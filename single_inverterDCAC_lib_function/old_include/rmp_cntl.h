/* =================================================================================
File name:        RMP_CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the RMPCNTL module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                   
------------------------------------------------------------------------------*/
#ifndef __RMP_CNTL_H__
#define __RMP_CNTL_H__

typedef struct { _iq    TargetValue; 	// Input: Target input
				 Uint32 RampDelayMax;	// Parameter: Maximum delay rate						  
				 _iq    RampHighLimit;	// Parameter: Maximum limit
				 Uint32 RampDelayCount; // Variable: Incremental delay	
				 _iq    SetpointValue;	// Output: Target output 				 
		  	  	 void (*calc)();	  	// Pointer to calculation function
				 } RMPCNTL;	            

typedef RMPCNTL *RMPCNTL_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/                     
#define RMPCNTL_DEFAULTS {  0, \
                            2500, \
                          	0, \
                          	0, \
                          	0, \
                   			(void (*)(Uint32))rmp_cntl_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in RMP_CNTL.C
------------------------------------------------------------------------------*/
void rmp_cntl_calc(RMPCNTL_handle);

#endif // __RMP_CNTL_H__
