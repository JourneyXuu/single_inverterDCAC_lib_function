#ifndef GPIO_H_
#define GPIO_H_

#include "DSP28x_Project.h"

#define LED_G_H()             GpioDataRegs.GPASET.bit.GPIO24 = 1//�̵���   G
#define LED_Y_H()             GpioDataRegs.GPASET.bit.GPIO17 = 1//�Ƶ���   Y
#define LED_R_H()             GpioDataRegs.GPASET.bit.GPIO20 = 1//�����   R

#define LED_G_L()             GpioDataRegs.GPACLEAR.bit.GPIO24 = 1//�̵���  G
#define LED_Y_L()             GpioDataRegs.GPACLEAR.bit.GPIO17 = 1//�Ƶ���  Y
#define LED_R_L()             GpioDataRegs.GPACLEAR.bit.GPIO20 = 1//����� R

void GPIOInit(void);

#endif
