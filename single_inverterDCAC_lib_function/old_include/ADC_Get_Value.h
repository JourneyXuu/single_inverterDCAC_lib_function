/* ==================================================================================
File name:       DSP2833xAD_VdcEI.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: This file contains source for the F2833x Two leg current measurement,
Two volatage measurement and DC-bus measurement driver.

Target: TMS320F2833x family

=====================================================================================
History:
-------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/

#ifndef __ADC_GET_VALUE_H__
#define __ADC_GET_VALUE_H__


/*-----------------------------------------------------------------------------
Define the structure of the ILEG2DCBUSMEAS Object
-----------------------------------------------------------------------------*/
typedef struct {   
				 float EabMeasGain;    // 1 Eab   Parameter: gain for Eab  
                 float EabMeasOffset;  // 1 Eab   Parameter: offset for Eab  
                 float EabMeas;        // 1 Eab   Output: measured Eab

                 float VdcMeasGain;   // 5 VdcP  Parameter: gain for VdcP
                 float VdcMeasOffset; // 5 VdcP  Parameter: offset for VdcP
                 float VdcMeas;       // 5 VdcP  Output: measured VdcP

                 float IaMeasGain;     // 6 Ia  Parameter: gain for Ia  
                 float IaMeasOffset;   // 6 Ia  Parameter: offset for Ia 
                 float IaMeas;         // 6 Ia  Output: measured Ia 

                 void (*calc)();       // Pointer to the read function
               } ADC_Get_Value;

typedef ADC_Get_Value *ADC_Get_handle;
/*-----------------------------------------------------------------------------
 Note 1 : It is necessary to call the init function to change the ADC 
            register settings, for the change in the channel setting for 
            ChSelect setting changes to take effect.
            The read function will not detect or act upon this change.
-----------------------------------------------------------------------------*/
/*
#define F2833X_VDCEIBUS_MEAS_DEFAULTS   { 3.3222591,5+0.306670,0,             \
                                          3.3222591,5+0.302190,0,             \
                                          3.3222591,5+0.284760,0,             \
                                          3.3222591,5+0.302190,0,             \
										  3.3222591,5+0.255496,0,             \
                                          3.3222591,5+0.318840,0,             \
                                          3.3222591,5+0.304240,0,             \
                                          3.3222591,5+0.316406,0,             \
                                          3.3222591,5+0.275030,0,             \
                                          (void (*)(Uint32))F2833X_VdcEIbus_drv_init, \
                                          (void (*)(Uint32))F2833X_VdcEIbus_drv_read  \
                                         }
										 */
#define ADC_Get_Value_DEFAULTS   { 30.093,50.193,0,             \
                                          23.193,0.6217,0,             \
                                          5.463,9.0143,0,             \
                                          (void (*)(Uint32))ADC_Get_Value_calc  \
                                         }

/*------------------------------------------------------------------------------
 Prototypes for the functions in F281XILEG_VDC.C
------------------------------------------------------------------------------*/
void ADC_Get_Value_calc(ADC_Get_handle);

#endif // __F281XILEG_VDC_H__


