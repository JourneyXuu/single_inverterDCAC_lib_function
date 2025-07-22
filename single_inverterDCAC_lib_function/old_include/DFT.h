/* ==================================================================================
File name:  DFT.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: �������źŽ��п��ٸ���Ҷ���������������źŵ���Чֵ

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
typedef struct { float Signal_In;     // Input: �ź�����  
                 float RMS;           // Output:��Чֵ��� 
                 float T;             // Parameter:�������� 
                 float N;             // Parameter:��������
                 float H;             // Parameter:�����źŴ���
				 float Counter_n;     // Variable: ѭ��������
                 float Real_number;   // Variable: �����ź�ʵ������ 
                 float Imag_number;   // Variable: �����ź���������	
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
