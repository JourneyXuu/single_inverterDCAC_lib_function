
#include "DSP28x_Project.h"
#include "System_Init.h"
#include <string.h>
#include <stdint.h>
#include "EPWM.h"
#include "Adc.h"
#include "Gpio.h"
#include "SCI.h"
#include "DMA.h"
//#include "Timer.h"
#include "SOGI.h"
#include "OLED.h"

//#pragma CODE_SECTION(AdcISR, "ramfuncs");

/*****************************************************************************
* ??    ??:void SysCtrlInit(void)
 * ??    ??: ?????????????????
 *?????????
 *      PLL????SYSCLKOUT = 60Mhz??
 *      EPWM1~5 ???????ADC???????
 *      HALT?????????????????1??????????
*****************************************************************************/
void SysCtrl_Init(void)
{
    DisableDog();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;// Enable ADC peripheral clock
    (*Device_cal)();
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;// Return ADC clock to original state
    EDIS;

    IntOsc1Sel();
    InitPll(DSP28_PLLCR,DSP28_DIVSEL);

    InitPeripheralClocks();    //Initialize the peripheral clocks

}

void Function_Module_Init(void)
{


    /*????????*/
    GPIOInit();
    Master_EPWM_Init();        //EPWM1
    Slave_EPWM_Init(&EPwm2Regs);//EPWM2
    //Slave_EPWM_Init(&EPwm3Regs);//EPWM3 
//    Slave_EPWM_Init(&EPwm4Regs);//EPWM4
//    Slave_EPWM_Init(&EPwm6Regs);//EPWM6

	OLED_Init();
    OLED_Refresh();
    OLED_Clear();

//    OLED_ShowChinese(0,0,0,16,1);//中
//    OLED_ShowChinese(18,0,1,16,1);//景
//    OLED_ShowChinese(36,0,2,16,1);//园
//    OLED_ShowChinese(54,0,3,16,1);//电
//    OLED_ShowChinese(72,0,4,16,1);//子
//    OLED_ShowChinese(90,0,5,16,1);//技
//    OLED_ShowChinese(108,0,6,16,1);//术

    OLED_ShowString(0,0,"Uab:",16,1);//6*8 “ABC”
    OLED_ShowString(0,16,"Udc:",16,1);//6*12 “ABC”
    OLED_ShowString(0,32,"Iab:",16,1);//8*16 “ABC”
    OLED_Refresh();//更新显示
    //DMA_Init();
    ADCTrig();
    ADC_Init();//?????????????ADC DMA
    //UART_Init(115200);//9600
    /*?????????*/
    //SVPWM_INIT(&SVPWM_Handle);
//    SOGI_Init();


    /*?????卸????*/
    //EALLOW;
    //PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//timer 0 ?卸?
    //EDIS;
    // Enable ADCINT1 in PIE
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // Enable INT 1.1 in the PIE
    IER |= M_INT1;
    PieCtrlRegs.PIEACK.all = 0xFFFF;//???????卸?
    //ADC/TIM0  TIM1
    //IER |= M_INT1 | M_INT13;//????卸??
    EINT;
    ERTM;

    /*??????????*/
    CpuTimer0Regs.TCR.bit.TSS = 0;
    CpuTimer1Regs.TCR.bit.TSS = 0;
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}
