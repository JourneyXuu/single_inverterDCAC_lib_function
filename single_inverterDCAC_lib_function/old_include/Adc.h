#ifndef ADC_H_
#define ADC_H_

typedef struct
{
    unsigned int Init_Flag;//AD是否已经初始化
    long    IAvg_Stand;//电流基准值
    long    IAvg;//输出电流平均值
    long    VAvg;//输出电电压平均值
    long    VaAvg;//滑动变阻器电压平均值
}ADC_STR;

extern ADC_STR Adc_Value;

void ADCTrig(void);
void ADC_Init(void);
__interrupt void AdcISR(void);

#endif
