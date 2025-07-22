/*
 * IIC.h
 *
 *  Created on:
 *      Author: DELL
 */

#ifndef IIC_H_
#define IIC_H_

#define u8 Uint8
#define u16 Uint16
#define u32 Uint32


#include "F2806x_Device.h"
#include "F2806x_Examples.h"


//SCL:GPIO28 SDA:GPIO29
#define OLED_SCL_Clr() GpioDataRegs.GPACLEAR.bit.GPIO28=1;
#define OLED_SCL_Set() GpioDataRegs.GPASET.bit.GPIO28=1;

#define OLED_SDA_Clr() GpioDataRegs.GPACLEAR.bit.GPIO29=1;
#define OLED_SDA_Set() GpioDataRegs.GPASET.bit.GPIO29=1;

//SCL:GPIO32 SDA:GPIO33
//#define OLED_SCL_Clr() GpioDataRegs.GPACLEAR.bit.GPIO32=1;
//#define OLED_SCL_Set() GpioDataRegs.GPASET.bit.GPI32=1;
//
//#define OLED_SDA_Clr() GpioDataRegs.GPACLEAR.bit.GPIO33=1;
//#define OLED_SDA_Set() GpioDataRegs.GPASET.bit.GPIO33=1;

void I2C_GPIO_Init();
//延时
void IIC_delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);


#endif /* APP_IIC_IIC_H_ */
