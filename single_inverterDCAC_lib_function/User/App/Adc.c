
#include "DSP28x_Project.h"
#include "Adc.h"
#include <string.h>
#include <stdint.h>
#include "EPWM.h"
#include "SOGI.h"


void ADC_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
    (*Device_cal)();
    EDIS;

    EALLOW;
    //�˴����� ˳��ɼ�
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;//����AD���������ж�
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;// ADC �ɼ������������ǣ�
    AdcRegs.ADCCTL2.bit.CLKDIV2EN=0;// ADCCLK = SYSCLKOUT(60Mhz)
    AdcRegs.SOCPRICTL.bit.ONESHOT = 0;// ADC ���βɼ����� 0 one shot disabled
    AdcRegs.SOCPRICTL.bit.RRPOINTER = 0x0F;// Round Robin Pointer
    AdcRegs.SOCPRICTL.bit.SOCPRIORITY=0x10;//SOC Priority
    /**/
    AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x00;    //ADCA0
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0X05;  //0x05:ADCTRIG5 �C ePWM1, ADCSOCA
    AdcRegs.ADCSOC0CTL.bit.ACQPS   = 0x5;   // ��������25*CLK  �ܹ�650ns
    /*�ߵ�ѹEab*/
    AdcRegs.ADCSOC1CTL.bit.CHSEL = 0x01;    //ADCA1
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0X05;  //0x05:ADCTRIG5 �C ePWM1, ADCSOCA
    AdcRegs.ADCSOC1CTL.bit.ACQPS   = 0x10;   // ��������25*CLK  �ܹ�650ns
    /**///Ԥ��
    //AdcRegs.ADCSOC2CTL.bit.CHSEL = 0x02;//ADCA2
    //AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0X11;//
    //AdcRegs.ADCSOC2CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /*ֱ��ĸ�ߵ�ѹVdc*/
    AdcRegs.ADCSOC2CTL.bit.CHSEL = 0X02;    //ADCA2
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0X05;  //
    AdcRegs.ADCSOC2CTL.bit.ACQPS   = 0x5;  // ��������25*CLK
    /*�ߵ���Iab*/
    AdcRegs.ADCSOC3CTL.bit.CHSEL = 0x03;    //ADCA3
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 0X05;  //0x05:ADCTRIG5 �C ePWM1, ADCSOCA
    AdcRegs.ADCSOC3CTL.bit.ACQPS   = 0x8;  // ��������25*CLK
    /**/
    AdcRegs.ADCSOC4CTL.bit.CHSEL = 0x04;//ADCA4
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 0X05;//
    AdcRegs.ADCSOC4CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC5CTL.bit.CHSEL = 0x05;//ADCA5
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 0X05;//
    AdcRegs.ADCSOC5CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC6CTL.bit.CHSEL = 0x06;//ADCA6
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0X05;//
    AdcRegs.ADCSOC6CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC7CTL.bit.CHSEL = 0x07;//ADC07
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL = 0X05;//
    AdcRegs.ADCSOC7CTL.bit.ACQPS   = 0x10;// ��������25*CLK

    /***********************ADCB*****************************8*/
    AdcRegs.ADCSOC8CTL.bit.CHSEL = 0x08;//ADCB0
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC8CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC9CTL.bit.CHSEL = 0x09;//ADCB1
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC9CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC10CTL.bit.CHSEL = 0x0A;//ADCB2
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC10CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC11CTL.bit.CHSEL = 0x0B;//ADCB3
    AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC11CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC12CTL.bit.CHSEL = 0x0C;//ADCB4
    AdcRegs.ADCSOC12CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC12CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC13CTL.bit.CHSEL = 0x0D;//ADCB5
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC13CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
    AdcRegs.ADCSOC14CTL.bit.CHSEL = 0x0E;//ADCB6
    AdcRegs.ADCSOC14CTL.bit.TRIGSEL = 0X00;//
    AdcRegs.ADCSOC14CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /**/
//    AdcRegs.ADCSOC14CTL.bit.CHSEL = 0x0F;//ADCB7
//    AdcRegs.ADCSOC14CTL.bit.TRIGSEL = 0X00;// ADCTRIG9 �C TIM7, ADCSOCA��������
//    AdcRegs.ADCSOC14CTL.bit.ACQPS   = 0x10;// ��������25*CLK
    /*ADC�ж�����*/
    // Disable continuous sampling for ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;//���һ�����ڵ�ת��������ж�
    AdcRegs.INTSEL1N2.bit.INT1SEL = 0x07;//ѡ��ͨ��14������ɺ�����ж��ź�
//    AdcRegs.ADCINTSOCSEL1.bit.SOC7 = 1;//ADCINT1�ж�Դѡ��
    AdcRegs.INTSEL1N2.bit.INT1E = 1;//ʹ��ADCint1�ж�

    PieCtrlRegs.PIEIFR1.bit.INTx1 = 0;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    IER |= M_INT1;
    /*ADC��ʼ�ɼ�*/
    AdcRegs.ADCCTL1.bit.ADCPWDN = 1;    // ADC ģ���·�ڲ���ģ���ϵ�
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;  // ADC �ο���·�ڲ���ģ���ϵ�
    AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;   // ADC Bandgap��·�ڲ���ģ���ϵ�
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 1;  // ADC�ⲿ�ڲ���ѹ�ο�1
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;  // ADC����
    /*ADC������ʼ��*/
    EDIS;
    DELAY_US(1000l);// ADC��ʼ ת��ǰ�ӳ�1ms ����������жϹ���
}

void ADCTrig(void)
{
    EALLOW;
/*
    EPwm1Regs.TBPRD = EPWM1_TBPRD;//50K=1200 100k=600 EPWM1_TBPRD
    EPwm1Regs.TBPHS.half.TBPHS = 0;//�����ƣ���������ʱ���ź�ͬ��
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//�������ϼ���ģʽ��
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;//slave ����
    EPwm1Regs.TBCTL.bit.PHSDIR = TB_DOWN;// Count DOWN on sync (=90 deg)
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;// ʹ�þ���Ĵ���,��ֱ�Ӳ���TBPRD�Ĵ���
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;//ync flow-through
    EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;// TBCLKʱ�ӷ�Ƶ�� TBCLK = SYSCLKOUT/(CLKDIV * HSPCLKDIV),CLKDIV = 1;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;// HSPCLKDIV = 1;  TBCLK = SYSCLKOUT(60Mhz);
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;// CMPA�Ĵ���ʹ�þ���ģʽ��
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// ��CTR = 0 ʱ����CMPA�����е����ݼ��ص�CMPAִ�мĴ����У�
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;// ��=CAMP���øߣ�=CBMPʱ����
    EPwm1Regs.AQCTLA.bit.CBU = AQ_CLEAR;
    EPwm1Regs.CMPA.half.CMPA= 0;
    */
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;//ʹ��SOCA��������
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;//Cnt=0 Event
    EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;//��������Generate pulse on 1st event
    EDIS;
}



/*
/�ж���ں���
__interrupt void AdcISR(void)
{
    if(AdcRegs.ADCINTFLG.bit.ADCINT1)//������ADC1�ж�
    {
        ADC_Get_Value(); //��ȡAD����

        //���AD�жϱ�־λ
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;//���жϱ�־λ ��ADC�ж����ö�Ӧ
        PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
        return;
    }
}
*/
