#include "ADC_Get_Value.h"
#include "IQmathLib.h"
#include "DSP28x_Project.h"
#include "Adc.h"
#include <string.h>
#include <stdint.h>

void ADC_Get_Value_calc(ADC_Get_Value *p)
{
    //输出电流  输出电压  滑动变阻器
    int16 DatQ15;
           //Uint16 Dat;
    float Tmp1;

    //  AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    //Udc
            DatQ15 = AdcResult.ADCRESULT1;
            //DatQ15 = Dat^0x8000;                      //Vdc Convert raw result to bipolar signal
            Tmp1 = 3.3  *( (float)(DatQ15)/ 4095.0);       //0xFFF0 ==>65520
            p->EabMeas = Tmp1;
            p->EabMeas = p->EabMeasGain * Tmp1;         // p->VdcMeas = gain*dat
            p->EabMeas -= p->EabMeasOffset;             // Add offset
//            p->EabMeas *= 20;                            // Positive direction
    //Ua
            DatQ15 = AdcResult.ADCRESULT2;
           // DatQ15 = Dat^0x8000;                      //eab Convert raw result to bipolar signal
            Tmp1 = 3.3  *( (float)DatQ15/ 4095.0);       //0xFFF0 ==>65520
            p->VdcMeas = Tmp1;
            p->VdcMeas = p->VdcMeasGain * Tmp1;         // p->EaMeas = gain*dat
            p->VdcMeas -= p->VdcMeasOffset;             // Add offset
//            p->VdcMeas *= 30.19;                            // Positive direction
    //Ia
            DatQ15 = AdcResult.ADCRESULT3;
           // DatQ15 = Dat^0x8000;                      //ebc Convert raw result to bipolar signal
            Tmp1 = 3.3  *( (float)DatQ15/ 4095.0);       //0xFFF0 ==>65520
            p->IaMeas = Tmp1;
            p->IaMeas = p->IaMeasGain * Tmp1;         // p->EbMeas = gain*dat
            p->IaMeas -= p->IaMeasOffset;             // Add offset
//            p->IaMeas *= 4.5;
}
