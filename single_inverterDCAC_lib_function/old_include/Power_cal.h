/* =================================================================================
File name:     Power_calc.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the droop.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                  
------------------------------------------------------------------------------*/
#ifndef __POWER_CAL_H__
#define __POWER_CAL_H__

typedef struct {  _iq  UAlpha;  		//  Frequency Reference
				  _iq  UBeta;	  	// Voltage Reference
                  _iq  IAlpha;	  	// Voltage Reference
                  _iq  IBeta;	  	// Voltage Reference
				  _iq  P_meas;	  	// P meas
				  _iq  Q_meas;	  	// Q meas
		 	 	  void (*calc)();	  	// Pointer to calculation function
				 } POWER_CALC;	            

typedef POWER_CALC *POWER_CALC_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the droop object.
-----------------------------------------------------------------------------*/                     
#define POWER_CALC_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
                          0, \
   				     	  (void (*)(Uint32))Power_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in droop.C
------------------------------------------------------------------------------*/
void Power_calc(POWER_CALC_handle);

#endif // __Power_cal_H__
