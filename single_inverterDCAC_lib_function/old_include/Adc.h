#ifndef ADC_H_
#define ADC_H_

typedef struct
{
    unsigned int Init_Flag;//AD�Ƿ��Ѿ���ʼ��
    long    IAvg_Stand;//������׼ֵ
    long    IAvg;//�������ƽ��ֵ
    long    VAvg;//������ѹƽ��ֵ
    long    VaAvg;//������������ѹƽ��ֵ
}ADC_STR;

extern ADC_STR Adc_Value;

void ADCTrig(void);
void ADC_Init(void);
__interrupt void AdcISR(void);

#endif
