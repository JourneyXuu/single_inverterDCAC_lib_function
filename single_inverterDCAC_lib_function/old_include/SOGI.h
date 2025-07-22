/* =================================================================================
File name:       SOGI.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the SOGI.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-4-2011	Version 1.00                                                  
------------------------------------------------------------------------------*/
#ifndef __SOGI_H__
#define __SOGI_H__

typedef struct {  float  u;  		// �����ѹ
				  float  we;	     	// ���������ѹƵ��
				  float  u_base;		    // ��� �����ѹ�еĻ�������
				  float  qu_base;         // ��� ����������������
				  float  delta_u;	     	// ���SOGI��ѹ�����
				  float  T;		               	//���ֲ���
				  float  last_integer1;            //������1��һʱ�����ֵ
                  float  last_integer2;            //������2��һʱ�����ֵ
                  float  last_middle1;             //������1��һʱ������ֵ
                  float  last_middle2;             //������2��һʱ������ֵ
				  float  k;			// ������SOGI����ϵ��
				  float  vdcm;
				  float  m1;
				  float  m2;
				  float  m3;
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } SOGI;	            

typedef SOGI *SOGI_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the Idq_NP_order object.
-----------------------------------------------------------------------------*/                     
#define SOGI_DEFAULTS {   0, \
                          2*PI*50, \
                          0, \
                          0, \
                          0, \
						  0.0001, \
						  0, \
						  0, \
						  0, \
						  0, \
                          0.5, \
                          0.1, \
                          0.0, \
                          0.0, \
                          0.0, \
              			  (void (*)(Uint32))SOGI_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SOGI.C
------------------------------------------------------------------------------*/
void SOGI_calc(SOGI_handle);

#endif // 
