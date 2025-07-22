/*
 * IIC.c
 *
 *  Created on:
 *      Author: DELL
 */

#include "IIC.h"

void I2C_GPIO_Init()
{
    EALLOW; 
    SysCtrlRegs.PCLKCR0.all=1;;             

    //GPIO28 GPIO29
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     
    GpioCtrlRegs.GPAMUX2.bit.GPIO28=0;      
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;     
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;    
    GpioCtrlRegs.GPAMUX2.bit.GPIO29=0;     
    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;   

    //GPIO32 GPIO33
//    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    
//    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;     
//    GpioCtrlRegs.GPBMUX1.bit.GPIO32=0;      
//    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;   
//
//    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;     
//    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     
//    GpioCtrlRegs.GPBMUX1.bit.GPIO33=0;      
//    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;   

//    GpioCtrlRegs.GPBMUX2.bit.GPIO52=0;
//    GpioCtrlRegs.GPBDIR.bit.GPIO52=1;
//    GpioCtrlRegs.GPBPUD.bit.GPIO52=1;
//    GpioDataRegs.GPBCLEAR.bit.GPIO52=1;

    EDIS;   
}

//延时
void IIC_delay(void)
{
	// u8 t=3;
//	u8 t=10;
//	while(t--);
    DELAY_US(1);

}

//起始信号
void I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();
//	IIC_delay();
	OLED_SDA_Clr();
//	IIC_delay();
	OLED_SCL_Clr();
//	IIC_delay();
}

//结束信号
void I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
//	IIC_delay();
	OLED_SDA_Set();
}

//等待信号响应
void I2C_WaitAck(void) //测数据信号的电平
{
	OLED_SDA_Set();
//	IIC_delay();
	OLED_SCL_Set();
//	IIC_delay();
	OLED_SCL_Clr();
//	IIC_delay();
}




