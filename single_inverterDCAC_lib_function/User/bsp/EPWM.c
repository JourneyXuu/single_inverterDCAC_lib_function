
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
    /*EPWM��������*/
    EPwm1Regs.TBPRD = EPWM1_TBPRD;//60M/50K=1200 60M/30K=2000
    EPwm1Regs.TBPHS.half.TBPHS = 0; //�����ƣ���������ʱ���ź�ͬ��
    EPwm1Regs.TBCTR = 0;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//������������ģʽ��
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;//�Ƿ����λ�Ĵ������ؼ�����
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;// ʹ�þ���Ĵ���,��ֱ�Ӳ���TBPRD�Ĵ���
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;//ʱ��ͬ���ͺ����ѡ��
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;// TBCLKʱ�ӷ�Ƶ�� TBCLK = SYSCLKOUT/(CLKDIV * HSPCLKDIV),CLKDIV = 1;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;// HSPCLKDIV = 1;  TBCLK = SYSCLKOUT(60Mhz);
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;// CMPA�Ĵ���ʹ�þ���ģʽ��
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;// CMPB�Ĵ���ʹ�þ���ģʽ��
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// PWM ����ģʽ CC_CTR_ZERO
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;// PWM ����ģʽ CC_CTR_ZERO
    /*�ߵ͵�ƽ�¼�����*/
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;//
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;//
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;//
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;//
    /*��ʱ���ж�����*/
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;//�������м�����ж�
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
    EPwm1Regs.ETSEL.bit.INTEN = 1;
    /*��������*/
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;//�����ź�Դ����ѡ��
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//��������λ��ѡ��������/�½���
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//����ѡ�񿪹�
    EPwm1Regs.DBFED = 80;//����8*1/60MHz
    EPwm1Regs.DBRED = 80;//����8*1/60MHz
    /*��ʼ����������ֵ*///������������ Ĭ�ϻ�����������A B��Ч
    EPwm1Regs.CMPA.half.CMPA = 0;// ��һ�����ڴ���
    EPwm1Regs.CMPB = 0;//������������ ����ʧЧ
    /*�ж�ʹ������*/
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
    //IER |= M_INT3;//�ж�ʹ�� EPWM1 INT3.1
    EDIS;
}

//��EPWM��ʼ��
void Slave_EPWM_Init(volatile struct EPWM_REGS* EPWM_Str)
{
    EALLOW;
    /*EPWM��������*/
    EPWM_Str->TBPRD = EPWM1_TBPRD;//
    EPWM_Str->TBPHS.half.TBPHS = 0;//EPWM1_TBPRD/2; //�����ƣ���������ʱ���ź�ͬ��
    EPWM_Str->TBCTR = 0;
    EPWM_Str->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//������������ģʽ��
    EPWM_Str->TBCTL.bit.PHSEN = TB_ENABLE;//�Ƿ����λ�Ĵ������ؼ�����
    EPWM_Str->TBCTL.bit.PRDLD = TB_SHADOW;// ʹ�þ���Ĵ���,��ֱ�Ӳ���TBPRD�Ĵ���
    EPWM_Str->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;//ʱ��ͬ���ͺ�����ѡ��
    EPWM_Str->TBCTL.bit.CLKDIV=TB_DIV1;// TBCLKʱ�ӷ�Ƶ�� TBCLK = SYSCLKOUT/(CLKDIV * HSPCLKDIV),CLKDIV = 1;
    EPWM_Str->TBCTL.bit.HSPCLKDIV=TB_DIV1;// HSPCLKDIV = 1;  TBCLK = SYSCLKOUT(60Mhz);
    EPWM_Str->CMPCTL.bit.SHDWAMODE = CC_SHADOW;// CMPA�Ĵ���ʹ�þ���ģʽ��
    EPWM_Str->CMPCTL.bit.SHDWBMODE = CC_SHADOW;// CMPB�Ĵ���ʹ�þ���ģʽ��
    EPWM_Str->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// PWM ����ģʽ CC_CTR_ZERO
    EPWM_Str->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;// PWM ����ģʽ CC_CTR_ZERO
    /*�ߵ͵�ƽ�¼�����*/
    EPWM_Str->AQCTLA.bit.CAU = AQ_CLEAR;//
    EPWM_Str->AQCTLA.bit.CAD = AQ_SET;//
    EPWM_Str->AQCTLB.bit.CBU = AQ_SET;//
    EPWM_Str->AQCTLB.bit.CBD = AQ_CLEAR;//
    /*��ʱ���ж�����*/
    EPWM_Str->ETSEL.bit.INTSEL = ET_CTR_PRD;//�������м�����ж�
    EPWM_Str->ETPS.bit.INTPRD = ET_1ST;
    EPWM_Str->ETSEL.bit.INTEN = 0;
    /*��������*/
    EPWM_Str->DBCTL.bit.IN_MODE = DBA_ALL;//�����ź�Դ����ѡ��
    EPWM_Str->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//��������λ��ѡ��������/�½���
    EPWM_Str->DBCTL.bit.POLSEL = DB_ACTV_HIC;//����ѡ�񿪹�
    EPWM_Str->DBFED = 80;//����8*1/60MHz
    EPWM_Str->DBRED = 80;//����8*1/60MHz
    /*��ʼ����������ֵ*///������������ Ĭ�ϻ�����������A B��Ч
    EPWM_Str->CMPA.half.CMPA = 0;//
    EPWM_Str->CMPB = 0;//������������ ����ʧЧ
    /*�ж�ʹ������*/
    //PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    //IER |= M_INT3;//�ж�ʹ�� EPWM1 INT3.1
    EDIS;
}

//���¼Ĵ�����ֵ

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

/*�ṹ���ʼ��*/
/*
void SVPWM_INIT(SVPWM_STRUCT* SVPWM_STR)
{
    SVPWM_STR->Num = 0;
    SVPWM_STR->Flag = 0;
}
*/
/*����ռ�ձ�*/
/*
static unsigned int Count_Limit(unsigned int Count)
{
    if(Count >= PWM_COUNT_MAX)Count = PWM_COUNT_MAX;
    if(Count <= PWM_COUNT_MIN)Count = PWM_COUNT_MIN;
    return Count;
}
*/
/*�ز����Ƽ���*/
/*
void EPWM_Count(SVPWM_STRUCT* SVPWM_STR)
{
    if(SVPWM_STR->Flag == 1)//��Ҫ����
    {
        if(SVPWM_STR->Num <= EPWM_MAX_HALF) //�벨,������P-O
        {
            SVPWM_STR->CNTA = EPWM1_TBPRD * sin((float)(SVPWM_STR->Num) * PWM_ANGLE);
            SVPWM_STR->CNTA = Count_Limit(SVPWM_STR->CNTA);//����ռ�ձ�
            SVPWM_STR->CNTB = 0;
        }
        else
        {   if(SVPWM_STR->Num < EPWM_MAX)
            {
                SVPWM_STR->CNTB = EPWM1_TBPRD * (1+sin((float)(SVPWM_STR->Num) * PWM_ANGLE));
                SVPWM_STR->CNTB = Count_Limit(SVPWM_STR->CNTB);//����ռ�ձ�
                SVPWM_STR->CNTA = 0;
            }
            if(SVPWM_STR->Num == EPWM_MAX)//ȫ��
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
    if(EPwm1Regs.ETFLG.bit.INT == 1)//���ж��¼�
    {
        SVPWM_Handle.Num++;

        if(SVPWM_Handle.Num == EPWM_MAX)//ȫ��
        {
            SVPWM_Handle.Num = 0;
        }
        if(SVPWM_Handle.Flag == 0)//�Ѽ������
        {
            RegReflash();
        }
        SVPWM_Handle.Flag = 1;//��Ҫ����
    }
    //
    EPwm1Regs.ETCLR.bit.INT = 1;//���жϱ�־λ
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
*/
/*
 * K��SOGI������������
 * W��SOGI����ͨ�����ź�Ƶ�ʣ�г��Ƶ��
 * */
/*
void PLL(float v_s1)
{
     //SOGI�����任�õ�����������v1_s(��)��v2_s(��)
     v0_s = ((v_s1-v1_s)*K-v2_s)*W;
     v1_s += v0_s*Ts;//�õ�V1(s)(��)
     v3_s += v1_s*Ts;
     v2_s = v3_s*W;//�õ�V2(s)(��)
     //����/dq�任��PI����
     v_q = sin(phase_angle)*(-1)*v1_s + cos(phase_angle)*v2_s;
     v_d = cos(phase_angle)*v1_s + sin(phase_angle)*v2_s;//�������Ҫ��ɾ��
     d_v_q = v_q_ref - v_q;//error
     v_q_temp += (d_v_q-d_v_q1) * Kp_PLL + d_v_q * Ki_PLL ;
     d_v_q1 = d_v_q;
     if(v_q_temp > 20 * pi)
         v_q_temp = 20 * pi;
     else if(v_q_temp < -20*pi)
         v_q_temp = -20 * pi;   //���ڶ����������޷�����ֹ������������ɲ������������С��phase_angle���ղ���������������
     //��ת�ٵõ���ǣ���ȡģ
     phase_angle += Ts * (100 * pi + v_q_temp);//��������ĽǶ����ۼ����ĽǶȣ�ͬʱҲ���źŵ�ǰ�ĽǶ�
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
