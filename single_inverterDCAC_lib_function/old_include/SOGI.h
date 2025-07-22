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

typedef struct {  float  u;  		// 输入电压
				  float  we;	     	// 输入电网电压频率
				  float  u_base;		    // 输出 输入电压中的基波分量
				  float  qu_base;         // 输出 基波分量的正交量
				  float  delta_u;	     	// 输出SOGI电压误差量
				  float  T;		               	//积分步长
				  float  last_integer1;            //积分器1上一时刻输出值
                  float  last_integer2;            //积分器2上一时刻输出值
                  float  last_middle1;             //积分器1上一时刻输入值
                  float  last_middle2;             //积分器2上一时刻输入值
				  float  k;			// 参数：SOGI带宽系数
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
