/* =================================================================================
File name:       dtime_comp.h  (IQ version)                  


Description: 
��������ģ�飬���ݵ���ʸ���ǣ���ɶԲ�ͬ�����µ���������
=====================================================================================
 History:
-------------------------------------------------------------------------------------
                                                
------------------------------------------------------------------------------*/
#ifndef __DTIME_H__
#define __DTIME_H__

typedef struct {  _iq  Ids;  		  // Input: d�����
				  _iq  Iqs;			  // Input: q����� 
				  _iq  Angle;		  // Input;��ת�Ƕ�����
				  _iq  Angle_I;       //output:�����Ƕ����
				  _iq  DC_bus;	  	  // Input:ֱ��ĸ�ߵ�ѹ����
				  float  Td_on_off;   // Input:��ͨ�ض�ʱ������
				  float  Td;          //Input������ʱ������
				  _iq  comp_alfa;     //Output��alfa�ಹ�����
				  _iq  comp_beta;     //Output��beta�ಹ�����
				  Uint16 sector;      //��һ������
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
