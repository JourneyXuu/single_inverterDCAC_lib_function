/* =================================================================================
File name:       FLL.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the FLL.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-4-2011	Version 1.00                                                  
------------------------------------------------------------------------------*/
#ifndef __FLL_H__
#define __FLL_H__

typedef struct {  _iq  qu;  		// ����SOGI�ͺ�90����� 
				  _iq  delta_u;	     	// ����SOGI��ѹ�����
				  _iq  theata;		    // ���������ѹ��λ��
				  _iq  we;         // ���������ѹƵ��
				  _iq  wff;		    // ��������ʼ������ѹ��Ƶ��
				  _iq  Ki;			// ������ ����ʱ�䳣��
				  _iq  T;			//���ֲ��� 
                  _iq  last_integer;            //�м��������һ����ʱ�̻������ֵ
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } FLL_cal;	            

typedef FLL_cal *FLL_cal_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the Idq_NP_order object.
-----------------------------------------------------------------------------*/                     
#define FLL_cal_DEFAULTS {   0, \
                          0, \
                          0, \
                          314, \
                          314, \
						  0.01, \
						  0.0001, \
                          0, \
              			  (void (*)(Uint32))FLL_angle_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in FLL.C
------------------------------------------------------------------------------*/
void FLL_angle_calc(FLL_cal_handle);

#endif // 
