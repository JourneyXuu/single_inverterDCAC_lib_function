/* ==================================================================================
File name:  DFT.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 对输入信号进行快速傅里叶分析，计算输入信号的有效值

Target: TMS320F2833x family

=====================================================================================
History:
-------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/

#ifndef __DFT_H__
#define __DFT_H__

/*-----------------------------------------------------------------------------
Define the structure of the DFT Object
-----------------------------------------------------------------------------*/
typedef struct { float Signal_In;     // Input: 信号输入  
                 float RMS;           // Output:有效值输出 
                 float T;             // Parameter:采样周期 
                 float N;             // Parameter:采样点数
                 float H;             // Parameter:输入信号次数
				 float Counter_n;     // Variable: 循环计数器
                 float Real_number;   // Variable: 输入信号实数部分 
                 float Imag_number;   // Variable: 输入信号虚数部分	
                 void  (*calc)();     // Pointer to the handle function 
               } DFT_Cal;

typedef DFT_Cal *DFT_Cal_handle;
/*-----------------------------------------------------------------------------
 Note 1 : It is necessary to call the init function to change the ADC 
            register settings, for the change in the channel setting for 
            ChSelect setting changes to take effect.
            The read function will not detect or act upon this change.
-----------------------------------------------------------------------------*/
#define DFT_Cal_DEFAULTS                { 0,             \
                                          0,             \
                                          0.0002,        \
                                          100,           \
										  1,             \
                                          0,             \
                                          0,             \
										  0,             \
                                          (void (*)(Uint32))DFT_Calculate }

/*------------------------------------------------------------------------------
 Prototypes for the functions in DFT.C
------------------------------------------------------------------------------*/
void DFT_Calculate(DFT_Cal *);

#endif // __DFT_H__
