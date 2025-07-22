
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
 * Function Name: void SysCtrl_Init(void)
 * Description:   Initializes the system control module, including disabling the watchdog timer,
 *                configuring ADC calibration, setting up the internal oscillator and PLL clock,
 *                and initializing peripheral clocks.
 *
 * Configuration Details:
 *                - Disables the watchdog timer to prevent unexpected resets
 *                - Enables ADC clock and performs ADC calibration for accurate conversions
 *                - Selects internal oscillator as the clock source and configures PLL to achieve
 *                  a system clock (SYSCLKOUT) of 60 MHz
 *                - Initializes peripheral clocks to prepare for module-specific operations
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
    ADC_Init();              // Initialize ADC module and configure for DMA operation
    // UART_Init(115200);    // Optional: Initialize UART with baud rate of 115200 (currently disabled)
    /* Module initialization section */
    // SVPWM_INIT(&SVPWM_Handle);  // Optional: Initialize SVPWM control (currently disabled)
    // SOGI_Init();               // Optional: Initialize SOGI filter (currently disabled)


    /* Configure PIE interrupt for ADC and CPU interrupt enable */
    // Enable ADC interrupt INT1.1 in PIE (commented out line was for Timer 0)
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // Enable ADC EOC interrupt (INT1.1)
    IER |= M_INT1;                       // Enable CPU interrupt INT1
    PieCtrlRegs.PIEACK.all = 0xFFFF;     // Acknowledge all PIE interrupts to clear any pending flags
    // Note: Other interrupts like Timer 0 or INT13 are not enabled in this configuration
    EINT;
    ERTM;

    /* Start CPU Timer 0 and Timer 1 */
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
