/*
 * OLED.h
 *
 *  Created on:
 *      Author: DELL
 */

#ifndef OLED_H_
#define OLED_H_

#include "DSP28x_Project.h"
#include "IIC.h"

#define OLED_CMD  0    // Command mode: selects OLED command register
#define OLED_DATA 1    // Data mode: selects OLED data register



void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);

void OLED_ShowFNum(u8 x,u8 y,float Fnum,u8 size1,u8 mode);
void OLED_ShowFloat(u8 x, u8 y, float Fnum, u8 size1, u8 mode) ;
void my_itoa(u8 num, char *buffer);
u8 get_int_length(u8 num);

void OLED_ShowFloat(u8 x,u8 y,float Fnum,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

