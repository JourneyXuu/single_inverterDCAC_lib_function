
#include "EPWM.h"
#include <Math.h>
//#include "Control.h"

SVPWM_STRUCT SVPWM_Handle;
extern float PWMshow=0;
extern float PWMtest=0;
void Master_EPWM_Init(void)
{
    PWMtest=EPWM1_TBPRD;
    EALLOW;
    /*EPWM基础配置*/
    EPwm1Regs.TBPRD = EPWM1_TBPRD;//60M/50K=1200 60M/30K=2000
    EPwm1Regs.TBPHS.half.TBPHS = 0; //不相移，计数器与时钟信号同步
    EPwm1Regs.TBCTR = 0;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//采用增减计数模式；
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;//是否从相位寄存器加载计数器
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;// 使用镜像寄存器,不直接操作TBPRD寄存器
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;//时钟同步型号输出选择
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;// TBCLK时钟分频； TBCLK = SYSCLKOUT/(CLKDIV * HSPCLKDIV),CLKDIV = 1;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;// HSPCLKDIV = 1;  TBCLK = SYSCLKOUT(60Mhz);
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;// CMPA寄存器使用镜像模式；
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;// CMPB寄存器使用镜像模式；
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// PWM 加载模式 CC_CTR_ZERO
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;// PWM 加载模式 CC_CTR_ZERO
    /*高低电平事件配置*/
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;//
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;//
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;//
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;//
    /*定时器中断配置*/
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;//计数到中间产生中断
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
    EPwm1Regs.ETSEL.bit.INTEN = 1;
    /*死区配置*/
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;//死区信号源输入选择
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//死区存在位置选择：上升沿/下降沿
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//极性选择开关
    EPwm1Regs.DBFED = 80;//死区8*1/60MHz
    EPwm1Regs.DBRED = 80;//死区8*1/60MHz
    /*初始化计数器数值*///配置完死区后 默认互补单独调节A B无效
    EPwm1Regs.CMPA.half.CMPA = 0;// 第一个周期待定
    EPwm1Regs.CMPB = 0;//设置完死区后 该项失效
    /*中断使能配置*/
    //EALLOW;
    // Enable CPU INT3 which is connected to EPWM1-3 INT:
/*
    IER |= M_INT1;
    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
       PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
       EDIS;
       PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
*/
    //PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    //IER |= M_INT3;//中断使能 EPWM1 INT3.1
    EDIS;
}

//从EPWM初始化
void Slave_EPWM_Init(volatile struct EPWM_REGS* EPWM_Str)
{
    EALLOW;
    /*EPWM基础配置*/
    EPWM_Str->TBPRD = EPWM1_TBPRD;//
    EPWM_Str->TBPHS.half.TBPHS = 0;//EPWM1_TBPRD/2; //不相移，计数器与时钟信号同步
    EPWM_Str->TBCTR = 0;
    EPWM_Str->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//采用增减计数模式；
    EPWM_Str->TBCTL.bit.PHSEN = TB_ENABLE;//是否从相位寄存器加载计数器
    EPWM_Str->TBCTL.bit.PRDLD = TB_SHADOW;// 使用镜像寄存器,不直接操作TBPRD寄存器
    EPWM_Str->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;//时钟同步型号输入选择
    EPWM_Str->TBCTL.bit.CLKDIV=TB_DIV1;// TBCLK时钟分频； TBCLK = SYSCLKOUT/(CLKDIV * HSPCLKDIV),CLKDIV = 1;
    EPWM_Str->TBCTL.bit.HSPCLKDIV=TB_DIV1;// HSPCLKDIV = 1;  TBCLK = SYSCLKOUT(60Mhz);
    EPWM_Str->CMPCTL.bit.SHDWAMODE = CC_SHADOW;// CMPA寄存器使用镜像模式；
    EPWM_Str->CMPCTL.bit.SHDWBMODE = CC_SHADOW;// CMPB寄存器使用镜像模式；
    EPWM_Str->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// PWM 加载模式 CC_CTR_ZERO
    EPWM_Str->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;// PWM 加载模式 CC_CTR_ZERO
    /*高低电平事件配置*/
    EPWM_Str->AQCTLA.bit.CAU = AQ_CLEAR;//
    EPWM_Str->AQCTLA.bit.CAD = AQ_SET;//
    EPWM_Str->AQCTLB.bit.CBU = AQ_SET;//
    EPWM_Str->AQCTLB.bit.CBD = AQ_CLEAR;//
    /*定时器中断配置*/
    EPWM_Str->ETSEL.bit.INTSEL = ET_CTR_PRD;//计数到中间产生中断
    EPWM_Str->ETPS.bit.INTPRD = ET_1ST;
    EPWM_Str->ETSEL.bit.INTEN = 0;
    /*死区配置*/
    EPWM_Str->DBCTL.bit.IN_MODE = DBA_ALL;//死区信号源输入选择
    EPWM_Str->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//死区存在位置选择：上升沿/下降沿
    EPWM_Str->DBCTL.bit.POLSEL = DB_ACTV_HIC;//极性选择开关
    EPWM_Str->DBFED = 80;//死区8*1/60MHz
    EPWM_Str->DBRED = 80;//死区8*1/60MHz
    /*初始化计数器数值*///配置完死区后 默认互补单独调节A B无效
    EPWM_Str->CMPA.half.CMPA = 0;//
    EPWM_Str->CMPB = 0;//设置完死区后 该项失效
    /*中断使能配置*/
    //PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    //IER |= M_INT3;//中断使能 EPWM1 INT3.1
    EDIS;
}

//更新寄存器数值

void PWMEn(void)
{
    EALLOW;
    PWMshow=10;
//    EPwm1Regs.TZCTL.bit.DCAEVT1 = 2;
//    EPwm1Regs.TZCTL.bit.DCAEVT1 = 2;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  =   1;// GPIO0 <-> EPWM1A
    GpioCtrlRegs.GPADIR.bit.GPIO0   =   1;// GPIO0 <-> EPWM1A
    GpioDataRegs.GPACLEAR.bit.GPIO0 =   1;// GPIO0 <-> EPWM1A

    GpioCtrlRegs.GPAMUX1.bit.GPIO1  =   1;// GPIO1 <-> EPWM1B
    GpioCtrlRegs.GPADIR.bit.GPIO1   =   1;// GPIO1 <-> EPWM1B
    GpioDataRegs.GPACLEAR.bit.GPIO1 =   1;// GPIO1 <-> EPWM1B

    GpioCtrlRegs.GPAMUX1.bit.GPIO2  =   1;// GPIO2 <-> EPWM2A
    GpioCtrlRegs.GPADIR.bit.GPIO2   =   1;// GPIO2 <-> EPWM2A
    GpioDataRegs.GPACLEAR.bit.GPIO2 =   1;// GPIO2 <-> EPWM2A

    GpioCtrlRegs.GPAMUX1.bit.GPIO3  =   1;// GPIO3 <-> EPWM2B
    GpioCtrlRegs.GPADIR.bit.GPIO3   =   1;// GPIO3 <-> EPWM2B
    GpioDataRegs.GPACLEAR.bit.GPIO3 =   1;// GPIO3 <-> EPWM2B
    EDIS;
}

void PWMDis_SS(void)
{
    EALLOW;
    PWMshow=100;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 =   0;//RELAY3
    GpioCtrlRegs.GPADIR.bit.GPIO0  =   1;
    GpioDataRegs.GPACLEAR.bit.GPIO0=   1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO1 =   0;//RELAY3
    GpioCtrlRegs.GPADIR.bit.GPIO1  =   1;
    GpioDataRegs.GPACLEAR.bit.GPIO1=   1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 =   0;//RELAY3
    GpioCtrlRegs.GPADIR.bit.GPIO2  =   1;
    GpioDataRegs.GPACLEAR.bit.GPIO2=   1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO3 =   0;//RELAY3
    GpioCtrlRegs.GPADIR.bit.GPIO3  =   1;
    GpioDataRegs.GPACLEAR.bit.GPIO3=   1;
    EDIS;
}

/*结构体初始化*/
/*
void SVPWM_INIT(SVPWM_STRUCT* SVPWM_STR)
{
    SVPWM_STR->Num = 0;
    SVPWM_STR->Flag = 0;
}
*/
/*限制占空比*/
/*
static unsigned int Count_Limit(unsigned int Count)
{
    if(Count >= PWM_COUNT_MAX)Count = PWM_COUNT_MAX;
    if(Count <= PWM_COUNT_MIN)Count = PWM_COUNT_MIN;
    return Count;
}
*/
/*载波调制计算*/
/*
void EPWM_Count(SVPWM_STRUCT* SVPWM_STR)
{
    if(SVPWM_STR->Flag == 1)//需要计算
    {
        if(SVPWM_STR->Num <= EPWM_MAX_HALF) //半波,工作在P-O
        {
            SVPWM_STR->CNTA = EPWM1_TBPRD * sin((float)(SVPWM_STR->Num) * PWM_ANGLE);
            SVPWM_STR->CNTA = Count_Limit(SVPWM_STR->CNTA);//限制占空比
            SVPWM_STR->CNTB = 0;
        }
        else
        {   if(SVPWM_STR->Num < EPWM_MAX)
            {
                SVPWM_STR->CNTB = EPWM1_TBPRD * (1+sin((float)(SVPWM_STR->Num) * PWM_ANGLE));
                SVPWM_STR->CNTB = Count_Limit(SVPWM_STR->CNTB);//限制占空比
                SVPWM_STR->CNTA = 0;
            }
            if(SVPWM_STR->Num == EPWM_MAX)//全波
            {
                SVPWM_STR->Num = 0;
            }
        }
        SVPWM_STR->Flag = 0;
    }
}
*/
/*
__interrupt void EPWM1_30K(void)
{
    if(EPwm1Regs.ETFLG.bit.INT == 1)//有中断事件
    {
        SVPWM_Handle.Num++;

        if(SVPWM_Handle.Num == EPWM_MAX)//全波
        {
            SVPWM_Handle.Num = 0;
        }
        if(SVPWM_Handle.Flag == 0)//已计算完成
        {
            RegReflash();
        }
        SVPWM_Handle.Flag = 1;//需要计算
    }
    //
    EPwm1Regs.ETCLR.bit.INT = 1;//清中断标志位
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
*/
/*
 * K：SOGI常数增益因子
 * W：SOGI允许通过的信号频率，谐振频率
 * */
/*
void PLL(float v_s1)
{
     //SOGI正交变换得到两个正交量v1_s(α)、v2_s(β)
     v0_s = ((v_s1-v1_s)*K-v2_s)*W;
     v1_s += v0_s*Ts;//得到V1(s)(α)
     v3_s += v1_s*Ts;
     v2_s = v3_s*W;//得到V2(s)(β)
     //αβ/dq变换及PI运算
     v_q = sin(phase_angle)*(-1)*v1_s + cos(phase_angle)*v2_s;
     v_d = cos(phase_angle)*v1_s + sin(phase_angle)*v2_s;//如果不需要就删掉
     d_v_q = v_q_ref - v_q;//error
     v_q_temp += (d_v_q-d_v_q1) * Kp_PLL + d_v_q * Ki_PLL ;
     d_v_q1 = d_v_q;
     if(v_q_temp > 20 * pi)
         v_q_temp = 20 * pi;
     else if(v_q_temp < -20*pi)
         v_q_temp = -20 * pi;   //用于对误差参数的限幅，防止误差参数过大造成不能输出正常大小的phase_angle最终不能正常进行锁相
     //由转速得到相角，并取模
     phase_angle += Ts * (100 * pi + v_q_temp);//这里输出的角度是累计误差的角度，同时也是信号当前的角度
     if(phase_angle > 2 * pi)
     {
         phase_angle -= 2 * pi;
     }
     if(phase_angle < 0)
     {
         phase_angle += 2 * pi;
     }
     angles[resultsIndex] = phase_angle;
}
*/
