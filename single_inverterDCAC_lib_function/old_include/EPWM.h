#ifndef EPWM_H_
#define EPWM_H_

#include "DSP28x_Project.h"

//#define PI 3.1415926

#define FREQUENCY   (10000)//PWM����Ƶ�� 10K
#define EPWM1_TBPRD   ( (90000000/FREQUENCY/2) - 1)//PWM����������ֵ 1000-1 2250

#define PWM_COUNT_MAX (EPWM1_TBPRD-10)//��ֵ�޷�
#define PWM_COUNT_MIN (10)

#define PUBLIC_FREQUENCY (50) //����Ƶ��
#define EPWM_MAX (FREQUENCY/PUBLIC_FREQUENCY)//�жϸ���=�������� = ����Ƶ��/����Ƶ�� 20k/50 = 400//���PWM����
#define EPWM_MAX_HALF (EPWM_MAX/2)//�����ڵ��Ʊ�

#define PWM_ANGLE ((2*PI)/EPWM_MAX)//������������Ʊ�
#define PWM_MODULATION (FREQUENCY)//�ջ���������Ʊ�

#define PWM_VALUE_MAX (EPWM_MAX)//�����޷�
#define PWM_VALUE_MIN (0)

//���㹫ʽ y1=m*sin(w*x)+C
//���㹫ʽ y2=-m*sin(w*x)+C
typedef struct
{
    unsigned int Num;//�жϼ���
    //unsigned int Modulation_Num;//���ƺ���ֵ
    unsigned int Flag;//�Ƿ������ɱ�־λ
    unsigned int CNTA;//ռ�ձ�
    unsigned int CNTB;
}SVPWM_STRUCT;

extern SVPWM_STRUCT SVPWM_Handle;

void Master_EPWM_Init(void);//��EPWM��ʼ��
void Slave_EPWM_Init(volatile struct EPWM_REGS* EPWM_Str);//��EPWM��ʼ��
void RegReflash(void);
void PWMEn1(void);
void PWMEn2(void);
void PWMDis_AC_MOS(void);
void PWMDis_AC_SCR(void);
void PWMDis_DC1(void);
void PWMDis_DC2(void);
void PWMDis_DC(void);
void PWMDis_AC(void);
void PWMDis_SS(void);
void PWMEn(void);
void SVPWM_INIT(SVPWM_STRUCT* SVPWM_STR);
void EPWM_Count(SVPWM_STRUCT* SVPWM_STR);

#endif
