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

typedef struct {  _iq  qu;  		// 输入SOGI滞后90°分量 
				  _iq  delta_u;	     	// 输入SOGI电压误差量
				  _iq  theata;		    // 输出电网电压相位角
				  _iq  we;         // 输出电网电压频率
				  _iq  wff;		    // 参数：初始电网电压角频率
				  _iq  Ki;			// 参数： 积分时间常数
				  _iq  T;			//积分步长 
                  _iq  last_integer;            //中间变量：上一采样时刻积分输出值
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
