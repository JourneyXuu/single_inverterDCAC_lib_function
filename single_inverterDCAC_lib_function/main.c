
#include "DSP28x_Project.h"//包含所用到控制函数头文件
#include <string.h>
#include <stdint.h>
#include "System_Init.h"
#include "EPWM.h"
#include <math.h>
//#include "SCI.h"
#include "SOGI.h"
#include "ADC_Get_Value.h"
#include "OLED.h"
#include "stdio.h"
#pragma CODE_SECTION(AdcISR,"ramfuncs");

    interrupt void AdcISR(void);
/* extern parameter define start*/
    float32 Ud=_IQ(150);        //直流给定电压
    float32 Umag=_IQ(28);       //直流给定电压
    float32 R=_IQ(1);           //有源阻尼系数
    float32 Idref=0.3;          // d轴电流参考值
    float32 Iqref=0;            // q轴电流参考值
    Uint16  Button_flag=0;      // 按钮标志位
    float32 PLL_delay=0;
    float32 DT_com=40;

    float32 P_ref=1000;
    float32 Q_ref=0;
    float32 V_ref=23;

    float32 V_mod=0;

    float32 det_I=0;
//////////////全局变量定义区//////////////
   float32 T=0.0005/ISR_FREQUENCY;    //IGBT开关周期
   float32 tao =0.0003183098;         //低通滤波器滤波系数,截止频率500Hz
   float32 Uds=0;  //直流电压
   float32 Grid_Ang=0; //电网旋转角度

    float32 Ang1=0;//电网旋转角度中间量
    float32 Ang=0;//电网旋转角度中间量
    float32 Ang2=0;//电网旋转角度中间量
    float32 K_ang=0.02;

    float32 Wt1=0;   //电网SPLL锁相环PI输出电网角频率

    float32 I_Ang=0;//三相电流PARK变换旋转角度
    float32 w_count=0;

    float32 Ut=0; //网侧所需电压幅值 Ut^2=（Ualpha)^2+（Ubeta)^2
    float32 Ualpha1=0; //SVPWM alpha调制电压
    float32 Ubeta1=0;  ////SVPWM beta调制电压

    Uint16 Watch_count=0;//观察数组计数器
    float data_test1=0;//观察数组计数器
    float data_test2=0;//观察数组计数器
    float data_test3=0;//观察数组计数器
    float data_test4=0;//观察数组计数器
    Uint16 pwmen_flag=0;
    Uint16 pwmdis_flag=0;
    Uint16 switch_flag=0;

   ///按键缓存区，按键扫描
    Uint16 key1_flag[4]={0};
    Uint16 key2_flag[4]={0};
    Uint16 key3_flag[4]={0};
    Uint16 key4_flag[4]={0};

    Uint16 key1_test=0;
    Uint16 key2_test=0;
    Uint16 key3_test=0;
    Uint16 key4_test=0;


   Uint16 Overcurrent_flag=0;


    volatile Uint16 EnableFlag=FALSE;//使能程序运行
    Uint16  RunFlag=0;//运行标志位

//    volatile CLARKE3H clark[3]={CLARKE3H_DEFAULTS,CLARKE3H_DEFAULTS,CLARKE3H_DEFAULTS};
    PARK park[4]={PARK_DEFAULTS,PARK_DEFAULTS,\
    PARK_DEFAULTS,PARK_DEFAULTS};
      //    park[0]=PARK_DEFAULTS; //3相电网电压park变换结构体，锁相环用
      //    park[1]=PARK_DEFAULTS; //3逆变器侧电压park变换结构体
      //    park[2]=PARK_DEFAULTS; //3相电网电流park变换结构体
      //    park[3]=PARK_DEFAULTS; //3相逆变器电流park变换结构体
      //    park[4]=PARK_DEFAULTS; //3相逆变器电流park变换结构体，控制信号用
      //    park[5]=PARK_DEFAULTS; //3相逆变器电流park变换结构体，控制信号用

      IPARK ipark1=IPARK_DEFAULTS; //PARK反变换
      XIANXIANG xianxiang1=Xian_Xiang_DEFAULTS; //电网线电压转相电压初始化
      XIANXIANG xianxiang2=Xian_Xiang_DEFAULTS; //逆变器线电压转相电压初始化

      POWER_CALC Power_calc1=POWER_CALC_DEFAULTS;//功率计算环节

      SOGI sogi1=SOGI_DEFAULTS;//功率计算环节
      SOGI sogi2=SOGI_DEFAULTS;//功率计算环节
      FLL_cal FLL1=FLL_cal_DEFAULTS;//功率计算环节

      ADC_Get_Value ADC_Get_Value1=ADC_Get_Value_DEFAULTS;//功率计算环节



      LOW_PASS_FILTER filter1=LOW_PASS_FILTER_DEFAULTS;
      LOW_PASS_FILTER filter2=LOW_PASS_FILTER_DEFAULTS;
      LOW_PASS_FILTER P_filter=LOW_PASS_FILTER_DEFAULTS;
      LOW_PASS_FILTER Q_filter=LOW_PASS_FILTER_DEFAULTS;

      PIDREG3 pid1[5]={PIDREG3_DEFAULTS,PIDREG3_DEFAULTS,\
      PIDREG3_DEFAULTS,PIDREG3_DEFAULTS,PIDREG3_DEFAULTS};

//            SVGENDQ svgen_dq1=SVGENDQ_DEFAULTS; //SVPWM模块初始化
       RAMPGEN rampgen1=RAMPGEN_DEFAULTS;  //模拟正余弦发生器
       RAMPGEN rampgen2=RAMPGEN_DEFAULTS;  //模拟正余弦发生器

       volatile float temp1[200];
       volatile float temp2[200];
       volatile float temp3[200];

       volatile float rate ;
       volatile float temp_vdc = 25;
       Uint32 OLED_count;
//            AD7656_Pro adc_meas1 = AD7656_Pro_DEFAULTS;  //AD7656转换结构体

void main(void)

{
    SysCtrl_Init();//系统初始化
    /*配置中断向量入口函数*/
        DINT;
        InitPieCtrl();//清空所有中断
        IER = 0x0000;
        IFR = 0x0000;
        InitPieVectTable();
        EALLOW;
        //    PieVectTable.EPWM1_INT = &EPWM1_30K;//定时器1中断函数向量定义
        PieVectTable.ADCINT1 = &AdcISR;//AD中断函数向量定义
        //PieVectTable.DINTCH1= &DMA_CH1_ISR;//DMA中断
        //PieVectTable.TINT1 = &ISR_200Hz;//定时器1中断函数向量定义
       //PieVectTable.TINT0 = &ISR_50KHz;//定时器0中断函数向量定义 TINT2
        EDIS;


        //将程序Copy至Ram中运行，加快程序运行速度
        #ifdef _FLASHOK
        //memcpy((uint16_t *)&RamfuncsLoadStart,(uint16_t *)&RamfuncsLoadEnd,(unsigned long)&RamfuncsRunStart);
        MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
        InitFlash();
        #endif
    Function_Module_Init();//各模块初始化
    PWMDis_SS();//封锁脉冲
    /////函数参数赋值
    rampgen1.StepAngleMax=2 * PI * BASE_FREQ * T;
    rampgen1.Umax=155.540;
    rampgen1.T_step=1;

    rampgen2.StepAngleMax=2 * PI * BASE_FREQ * T*2;
    rampgen2.Umax=155.540*0.2;
    rampgen2.T_step=1;

        pid1[0].Kp=_IQ(0.035); //PI调节器比例系数
        pid1[0].Ki=_IQ(T/0.008); //T/PI调节器积分系数 原T/(Kp/KI)
        pid1[0].Kd=_IQ(0/T); //PI调节器微分系�/T
        pid1[0].Kc=_IQ(0); //PI调骰中Ｕ凳�
        pid1[0].OutMax=_IQ(3); //PI调节器舷�
        pid1[0].OutMin=_IQ(-3); //PI调节器下限
        pid1[0].OutMax1=_IQ(3);
        pid1[0].OutMin1=_IQ(-3);

       //Q_Current
        pid1[4].Kp=_IQ(0.035); //PI调节器比例系数
        pid1[4].Ki=_IQ(T/0.008); //T/PI调节器分系数0.088
        pid1[4].Kd=_IQ(0/T); //PI调节器微分系数/T
        pid1[4].Kc=_IQ(0); //PI调节中５�?
        pid1[4].OutMax=_IQ(3); //PI调节器上限
        pid1[4].OutMin=_IQ(-3); //PI调节器下限
        pid1[4].OutMax1=_IQ(3); //PI调节器上限
        pid1[4].OutMin1=_IQ(-3); //PI调节器下限

    //PLL
       pid1[1].Kp=_IQ(2); //PI调节器比例系数
       pid1[1].Ki=_IQ(T/0.05); //T/PI调节器积分系数 原T/(Kp/KI)
       pid1[1].Kd=_IQ(0/T); //PI调节器微分系�/T
       pid1[1].Kc=_IQ(0); //PI调骰中Ｕ凳�
       pid1[1].OutMax=_IQ(135); //PI调节器舷�
       pid1[1].OutMin=_IQ(-135); //PI调节器下限
       pid1[1].OutMax1=_IQ(135);
       pid1[1].OutMin1=_IQ(-135);

    // 初始化d轴电流环PI调节器
       pid1[2].Kp=_IQ(14); //PI调节器比例系数
       pid1[2].Ki=_IQ(T/0.04);//; //T/PI调节器积分系数 原T/(Kp/KI)0.03
       pid1[2].Kd=_IQ(0/T); //PI调节器微分系数/T
       pid1[2].Kc=_IQ(0); //PI调节器积分校正系数
       pid1[2].OutMax=_IQ(15); //PI调节器上限
       pid1[2].OutMin=_IQ(-15); //PI调节器下限
       pid1[2].OutMax1=_IQ(15);
       pid1[2].OutMin1=_IQ(-15);
    // 初始化q轴电流环PI调节器
       pid1[3].Kp=_IQ(14); //PI调节器比例系数
       pid1[3].Ki=_IQ(T/0.04); //T/PI调节器积分系数 原T/(Kp/KI)
       pid1[3].Kd=_IQ(0/T); //PI调节器微分系数/T
       pid1[3].Kc=_IQ(0); //PI调节器积分校正系数
       pid1[3].OutMax=_IQ(25); //PI调节器上限
       pid1[3].OutMin=_IQ(-25); //PI调节器下限
       pid1[3].OutMax1=_IQ(25);
       pid1[3].OutMin1=_IQ(-25);

       tao=0.0001;
       filter1.K1=_IQdiv(_IQ(tao),(_IQ(tao)+_IQ(T)));
       filter1.K2=_IQdiv(_IQ(T),(_IQ(tao)+_IQ(T)));

       tao=0.003;
       filter1.K1=_IQdiv(_IQ(tao),(_IQ(tao)+_IQ(T)));
       filter1.K2=_IQdiv(_IQ(T),(_IQ(tao)+_IQ(T)));


    while(1)
    {
        //EPWM_Count(&SVPWM_Handle);
        //IQ_SOGI_Calc(&IQ_SOGI_FUNCTION);
        if (R>1000)
        {R=0;}
        else
        {R++;}
        if(OLED_count > 60000)
        {
            OLED_count = 1;
        }
        else
        {OLED_count++;}
        if(OLED_count == 1)
        {
            OLED_ShowFloat(33,0,ADC_Get_Value1.EabMeas,16,1);
//            OLED_ShowFloat(33,0,filter2.out,16,1);
            OLED_ShowFloat(33,16,ADC_Get_Value1.VdcMeas,16,1);
            OLED_ShowFloat(33,32,ADC_Get_Value1.IaMeas,16,1);
            OLED_Refresh();//更新显示
        }
//////key test
        key1_flag[3]=key1_flag[2];
        key1_flag[2]=key1_flag[1];
        key1_flag[1]=key1_flag[0];
        key1_flag[0]=GpioDataRegs.GPBDAT.bit.GPIO51;

        if (key1_flag[0]==0 && key1_flag[1]==0 && key1_flag[2]==1 && key1_flag[3]==1)
        {
           // key1_test=1;
            Button_flag=1;
        }

        key2_flag[3]=key2_flag[2];
        key2_flag[2]=key2_flag[1];
        key2_flag[1]=key2_flag[0];
        key2_flag[0]=GpioDataRegs.GPADAT.bit.GPIO12;

        if (key2_flag[0]==0 && key2_flag[1]==0 && key2_flag[2]==1 && key2_flag[3]==1)
        {
            //key2_test=1;
            Button_flag=2;
        }

        key3_flag[3]=key3_flag[2];
        key3_flag[2]=key3_flag[1];
        key3_flag[1]=key3_flag[0];
        key3_flag[0]=GpioDataRegs.GPBDAT.bit.GPIO50;

        if (key3_flag[0]==0 && key3_flag[1]==0 && key3_flag[2]==1 && key3_flag[3]==1)
        {
            V_ref=V_ref+2;
            Idref=Idref+0.1;
            if (Idref>3)
              {Idref=3;}
            if (V_ref>28)
              {V_ref=28;}
        }

        key4_flag[3]=key4_flag[2];
        key4_flag[2]=key4_flag[1];
        key4_flag[1]=key4_flag[0];
        key4_flag[0]=GpioDataRegs.GPADAT.bit.GPIO30;

        if (key4_flag[0]==0 && key4_flag[1]==0 && key4_flag[2]==1 && key4_flag[3]==1)
        {Idref=Idref-0.1;
        V_ref=V_ref-2;
            if (Idref<0.1)
                {Idref=0.1;}
            if (V_ref<16)
                {V_ref=16;}
        }
    }

}

///中断函数
interrupt void AdcISR(void)
{
/*
         if (switch_flag==1)
         {

         }
         else
         {

         }
*/
if(AdcRegs.ADCINTFLG.bit.ADCINT1)//产生了ADC1中断
{
     ADC_Get_Value1.calc(&ADC_Get_Value1);
//     if (ADC_Get_Value1.EabMeas>35 || ADC_Get_Value1.EabMeas<-35 || ADC_Get_Value1.IaMeas>4 || ADC_Get_Value1.IaMeas<-4 || ADC_Get_Value1.VdcMeas >50 || ADC_Get_Value1.VdcMeas <25)//
////     //if (key1_test>10 || key1_test<-10)
//     {
//         Overcurrent_flag++;
//         if (Overcurrent_flag>2)
//         {
//         //GpioDataRegs.GPADAT.bit.GPIO8=0;
//         PWMDis_SS();
//         Button_flag=2;
//         Overcurrent_flag=0;
//         key4_test=1;
//         }
//     }

//         rampgen2.calc(&rampgen2);
        if (Ud>200) {Ud=0;}
        else        {Ud++;}
        //SOGI 运算
        filter1.in=ADC_Get_Value1.VdcMeas;
        filter1.calc(&filter1);


        rampgen1.Umax=22;//filter1.out*0.8;//Umag;
        rampgen1.calc(&rampgen1);


        if (filter1.out<5)
        {filter1.out=5;}
        //   离网 离网 离网 离网 离网
        sogi1.u=-ADC_Get_Value1.EabMeas;//rampgen1.Sine;//ADC_Get_Value1.EabMeas
        sogi1.calc(&sogi1);
        FLL1.qu=sogi1.qu_base;
        FLL1.delta_u=sogi1.delta_u;//-filter1.out;
        FLL1.calc(&FLL1);
        if(FLL1.we<290)
        {FLL1.we=290;}
        if(FLL1.we>345)
        {FLL1.we=345;}
        sogi1.we=100*PI;//FLL1.we;//

        Umag=sqrt(sogi1.qu_base* sogi1.qu_base + sogi1.u_base * sogi1.u_base);
        filter2.in= Umag;
        filter2.calc(filter2);

        sogi2.u=ADC_Get_Value1.IaMeas;//ADC_Get_Value1.EabMeas
        sogi2.calc(&sogi2);
        sogi2.we=100*PI;//FLL1.we;//

        // PLL
        pid1[1].Ref = park[1].Qs;                //需要得到的正序Uq
        pid1[1].Fdb = 0;
        pid1[1].calc(&pid1[1]);
            Ang1 = 100*PI;// + pid1[1].Out;
            Ang = Ang + Ang1 * T;
            if(Ang > 6.283185308)
            {Ang -= 6.283185308;}
            else if(Ang < -6.283185308)
            {Ang += 6.283185308;}
        // 网侧相电压park变换
             park[1].Alpha = sogi1.u;//_base;
             park[1].Beta = sogi1.qu_base;
             park[1].Angle = Ang;
             park[1].calc(&park[1]);


      if (Button_flag==1)
          {

        // 等待锁相完成
             if(RunFlag == 0)
             {
                 PLL_delay++;

                if (PLL_delay>15000)
                {
                    GpioDataRegs.GPBDAT.bit.GPIO57=0;
                    GpioDataRegs.GPADAT.bit.GPIO14=0;
                    // close the relay, after the pro-charge of the dc capacitor
                }
               if(PLL_delay>20000)
               {
                   PLL_delay=0;
                   RunFlag=1;
                 //PWMEn();
               }
             }
            if (RunFlag==1)
            {

        // 网侧相电流park变换
             park[2].Alpha = sogi2.u;//_base;//-ADC_Get_Value1.IaMeas;//ADC_Get_Value1.IaMeas;
             park[2].Beta = sogi2.qu_base;
             park[2].Angle = Ang;
             park[2].calc(&park[2]);

        //       离网 离网  离网 离网  离网 离网  离网 离网  离网 离网  离网 离网
        // d电压PI
             pid1[0].Ref = V_ref;
             pid1[0].Fdb = park[1].Ds;//ADC_Get_Value1.VdcMeas;//Udc
             pid1[0].calc(&pid1[0]);

             // q电压PI
                  pid1[4].Ref = 0;
                  pid1[4].Fdb = park[1].Qs;//Udc
                  pid1[4].calc(&pid1[4]);

                  // d电压PI

                  // d轴PI
                       pid1[2].Ref=pid1[0].Out;//Idref;//pid1[0].Out;//0.7;//
                       pid1[2].Fdb=park[2].Ds;
                       pid1[2].calc(&pid1[2]);

                  // q轴PI
                       pid1[3].Ref= pid1[4].Out;//0;//pid1[4].Out;//0;
                       pid1[3].Fdb=park[2].Qs;
                       pid1[3].calc(&pid1[3]);


        /// 前馈补偿
             ipark1.Ds = pid1[2].Out;//park[1].Ds+//;;//+pid1[0].Out;//park[2].Ds*1.5;//+V_ref;//+sogi1.u_base;//wL=1.665  10;//
             ipark1.Qs = pid1[3].Out;//park[1].Qs+;//pid1[4].Out;//+sogi1.qu_base;//0;//+sogi1.qu_base;//wL=1.665
             ipark1.Angle = Ang;
             ipark1.calc(&ipark1);
/*
             //
             //       并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网 并网
                     // d电压PI

                     // d轴PI
                          pid1[2].Ref=Idref;//pid1[0].Out;//0.7;//
                          pid1[2].Fdb=park[2].Ds;
                          pid1[2].calc(&pid1[2]);

                     // q轴PI
                          pid1[3].Ref= 0;//pid1[4].Out;//0;
                          pid1[3].Fdb=park[2].Qs;
                          pid1[3].calc(&pid1[3]);

                     /// 前馈补偿
                          ipark1.Ds = pid1[2].Out+park[1].Ds;//+park[1].Ds;//34;//+sogi1.u_base;;//park[2].Ds*1.5;//+V_ref;//+sogi1.u_base;//wL=1.665  10;//
                          ipark1.Qs = pid1[3].Out+park[1].Qs;//0;//;//+0;//+sogi1.qu_base;//0;//+sogi1.qu_base;//wL=1.665
                          ipark1.Angle = Ang;
                          ipark1.calc(&ipark1);
                          //
*/
        //模拟正弦波/
        /*
            //模拟正弦波，幅值60V，直流电压
            sim_Ualpha=60*sin(sin_i/100.0*6.283185306);
            sim_Ubeta=60*sin(sin_i/100.0*6.283185306-1.5707963265);//减2*pi
            sin_i++;
           if(sin_i>=100){sin_i=0;}//周期20ms
            svgen_three.Ualpha = sim_Ualpha;//给定Ualpha分量
            svgen_three.Ubeta = sim_Ubeta;  //给定Ubeta分量
            svgen_three.Udc = 140;
            svgen_three.calc(&svgen_three);

        */
        /************* 计算SVPWM三相空占比 *************/
/*
            svgen_three.Ualpha = ipark_U.Alpha;
            svgen_three.Ubeta = ipark_U.Beta;
            //限幅
            Ut = sqrt(svgen_three.Ualpha * svgen_three.Ualpha +  svgen_three.Ubeta *  svgen_three.Ubeta);
            Umax = mppt.Vref/1.732;
            if(Ut > Umax)
            {
                svgen_three.Ualpha = svgen_three.Ualpha * Umax / Ut;
                svgen_three.Ubeta = svgen_three.Ubeta * Umax / Ut;
            }
            svgen_three.Udc = adc_meas.VdcNMeas + adc_meas.VdcPMeas;
            svgen_three.calc(&svgen_three);
*/
        /***********更新PWM的CMPA*************/
/*
            pwmgen.MfuncC1=svgen_three.Ta1;
            pwmgen.MfuncC2=svgen_three.Ta2;
            pwmgen.MfuncC3=svgen_three.Tb1;
            pwmgen.MfuncC4=svgen_three.Tb2;
            pwmgen.MfuncC5=svgen_three.Tc1;
            pwmgen.MfuncC6=svgen_three.Tc2;
            pwmgen.update(&pwmgen);

            } //PLL_delay结束
*/
             V_mod=ipark1.Alpha-ADC_Get_Value1.EabMeas;//;//rampgen1.Sine;//sogi1.u_base;//+

             if (V_mod>filter1.out*0.99)
             {
                 V_mod=filter1.out*0.99;
             }
             if (V_mod<-filter1.out*0.99)
             {
                 V_mod=-filter1.out*0.99;
             }
             //data_test1=(V_mod/40+1)*0.5*4499;
             //data_test2=(-V_mod/40+1)*0.5*4499;


             temp_vdc = filter1.out;//ADC_Get_Value1.VdcMeas;
             if(temp_vdc > 45.0) {temp_vdc = 45.0;}
             if(temp_vdc < 5.0) {temp_vdc = 5.0;}
             rate = 1.0 / temp_vdc;
             /* 正确写法：转换包裹完整表达式 */
           //  data_test1 = (rampgen1.Sine * rate + 1) * 0.5 * (EPWM1_TBPRD - 1);
          //   data_test2=(-rampgen1.Sine * rate +1)*0.5*(EPWM1_TBPRD-1);

             if (sogi2.u_base>0)
                 {
                 data_test3=DT_com;
                 data_test4=-DT_com;
                 }
             if (sogi2.u_base<0)
             {
                 data_test3=-DT_com;
                 data_test4=DT_com;
             }
//             data_test1=(rampgen1.Sine*0.1/ADC_Get_Value1.VdcMeas+1)*0.5*4499;
//             data_test2=(-rampgen1.Sine*0.1/ADC_Get_Value1.VdcMeas+1)*0.5*4499;
//             data_test1=(V_mod/36+1)*0.5*(EPWM1_TBPRD-1);
//             data_test2=(-V_mod/36+1)*0.5*(EPWM1_TBPRD-1);

             data_test1=(V_mod * rate+1)*0.5*(EPWM1_TBPRD-1)+data_test3;
             data_test2=(-V_mod * rate+1)*0.5*(EPWM1_TBPRD-1)-data_test3;
             if (data_test1>(EPWM1_TBPRD - 2)){data_test1=EPWM1_TBPRD - 2;}
             if (data_test1<2){data_test1=2;}
             if (data_test2>(EPWM1_TBPRD - 2)){data_test2=EPWM1_TBPRD - 2;}
             if (data_test2<2){data_test2=2;}

                 EPwm1Regs.CMPA.half.CMPA = (unsigned short)(data_test1);//(0.
                // 5*(EPWM1_TBPRD-1));//data_test1;
                 EPwm2Regs.CMPA.half.CMPA = (unsigned short)(data_test2);
                 if(pwmen_flag==0)
                 {
                     PWMEn();
                     pwmen_flag=1;
                     pwmdis_flag=0;
                 }
             }
   }
 }
/*********** graph中观察 *************/
     Watch_count++;
    if(Watch_count==200)
    Watch_count=0;

//    temp1[Watch_count]=(float)(sogi1.u_base);//EabMeas//VdcMeas//IaMeas//filter1.out//VdcMeas//sogi1.u_baserampgen1.Sine//sogi2.u_base//ADC_Get_Value1.IaMeas
    temp1[Watch_count]=(float)(ADC_Get_Value1.EabMeas);
    temp2[Watch_count]=(float)(ADC_Get_Value1.VdcMeas);
    temp3[Watch_count]=(float)(ADC_Get_Value1.IaMeas);
    //temp2[Watch_count]=(float)(Ang);
    // temp[2][Watch_count]=(float)(rampgen2.Sine);
 if (Button_flag!=1)
 {
     if(pwmdis_flag==0)
     {
        // EPwm1Regs.CMPA.half.CMPA = (unsigned short)(0);//(0.5*(EPWM1_TBPRD-1));//data_test1;
        // EPwm2Regs.CMPA.half.CMPA = (unsigned short)(0);
         PWMDis_SS();
         pwmdis_flag=1;
         pwmen_flag=0;
         GpioDataRegs.GPBDAT.bit.GPIO57=1;
         GpioDataRegs.GPADAT.bit.GPIO14=1;
     }

     ///关闭寄存器


     //PI 初始化
           pid1[0].Out=_IQ(0); //PI调节器比例系数
           pid1[0].Ui=_IQ(0); //T/PI调节器积分系数 原T/(Kp/KI)
           pid1[0].Ud=_IQ(0); //PI调节器微分系�/T
        //PLL
           pid1[1].Out=_IQ(0); //PI调节器比例系数
           pid1[1].Ui=_IQ(0); //T/PI调节器积分系数 原T/(Kp/KI)
           pid1[1].Ud=_IQ(0); //PI调节器微分系�/T

        // 初始化d轴电流环PI调节器
           pid1[2].Out=_IQ(0); //PI调节器比例系数
           pid1[2].Ui=_IQ(0); //T/PI调节器积分系数 原T/(Kp/KI)
           pid1[2].Ud=_IQ(0); //PI调节器微分系�/T
        // 初始化q轴电流环PI调节器
           pid1[3].Out=_IQ(0); //PI调节器比例系数
           pid1[3].Ui=_IQ(0); //T/PI调节器积分系数 原T/(Kp/KI)
           pid1[3].Ud=_IQ(0); //PI调节器微分系�/T

           //Q_Current
           pid1[4].Out=_IQ(0); //PI调节器比例系数
           pid1[4].Ui=_IQ(0); //T/PI调节器积分系数 原T/(Kp/KI)
           pid1[4].Ud=_IQ(0); //PI调节器微分系�/T

           RunFlag = 0;
 }
        /*********** return *************/
            //清除AD中断标志位
 //EPwm1Regs.CMPA.half.CMPA = (unsigned short)(0.5*(EPWM1_TBPRD-1));//(data_test1);//data_test1;

          AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        //Clear ADCINT1 flag reinitialize for next SOC
          PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

          return;

}
