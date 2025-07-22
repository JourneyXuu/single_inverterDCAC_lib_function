/* =================================================================================
File name:       dtime_comp.h  (IQ version)                  


Description: 
死区补偿模块，根据电流矢量角，完成对不同扇区下的死区补偿
=====================================================================================
 History:
-------------------------------------------------------------------------------------
                                                
------------------------------------------------------------------------------*/
#ifndef __DTIME_H__
#define __DTIME_H__

typedef struct {  _iq  Ids;  		  // Input: d轴电流
				  _iq  Iqs;			  // Input: q轴电流 
				  _iq  Angle;		  // Input;旋转角度输入
				  _iq  Angle_I;       //output:电流角度输出
				  _iq  DC_bus;	  	  // Input:直流母线电压输入
				  float  Td_on_off;   // Input:开通关断时间输入
				  float  Td;          //Input：死区时间输入
				  _iq  comp_alfa;     //Output：alfa相补偿输出
				  _iq  comp_beta;     //Output：beta相补偿输出
				  Uint16 sector;      //哪一个扇区
		 	 	  void  (*calc)();	  // Pointer to calculation function
				 } DT_COMP;	            

typedef DT_COMP * DT_COMP_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define DT_COMP_DEFAULTS {0,0,0,0,0,0,0,0,0,0,(void (*)(Uint32))dt_comp_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void dt_comp_calc(DT_COMP_handle);

#endif // __DTIME_H__
