#ifndef EPWM_H_
#define EPWM_H_

#include "DSP28x_Project.h"

//#define PI 3.1415926

#define FREQUENCY   (10000)//PWM开关频率 10K
#define EPWM1_TBPRD   ( (90000000/FREQUENCY/2) - 1)//PWM设置最大计数值 1000-1 2250

#define PWM_COUNT_MAX (EPWM1_TBPRD-10)//幅值限幅
#define PWM_COUNT_MIN (10)

#define PUBLIC_FREQUENCY (50) //公网频率
#define EPWM_MAX (FREQUENCY/PUBLIC_FREQUENCY)//中断个数=采样个数 = 开关频率/公网频率 20k/50 = 400//最大PWM个数
#define EPWM_MAX_HALF (EPWM_MAX/2)//半周期调制比

#define PWM_ANGLE ((2*PI)/EPWM_MAX)//开环横坐标调制比
#define PWM_MODULATION (FREQUENCY)//闭环横坐标调制比

#define PWM_VALUE_MAX (EPWM_MAX)//横轴限幅
#define PWM_VALUE_MIN (0)

//计算公式 y1=m*sin(w*x)+C
//计算公式 y2=-m*sin(w*x)+C
typedef struct
{
    unsigned int Num;//中断计数
    //unsigned int Modulation_Num;//调制后数值
    unsigned int Flag;//是否计算完成标志位
    unsigned int CNTA;//占空比
    unsigned int CNTB;
}SVPWM_STRUCT;

extern SVPWM_STRUCT SVPWM_Handle;

void Master_EPWM_Init(void);//主EPWM初始化
void Slave_EPWM_Init(volatile struct EPWM_REGS* EPWM_Str);//从EPWM初始化
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
