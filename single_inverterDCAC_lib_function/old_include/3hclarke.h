
/* =================================================================================
File name:       CLARKE3H.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the CLARKEH.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                   
------------------------------------------------------------------------------*/
#ifndef __CLARKE3H_H__
#define __CLARKE3H_H__

typedef struct {  _iq  As;  		// Input: phase-a stator variable
				  _iq  Bs;			// Input: phase-b stator variable
				  _iq  Cs;          // Input: phase-c stator variable
				  _iq  Alpha;		// Output: stationary d-axis stator variable 
				  _iq  Beta;		// Output: stationary q-axis stator variable
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } CLARKE3H;	            

typedef CLARKE3H *CLARKE3H_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CLARKE3H object.
-----------------------------------------------------------------------------*/                     
#define CLARKE3H_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))clarke3h_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE3H.C
------------------------------------------------------------------------------*/
void clarke3h_calc(CLARKE3H_handle);

#endif // __CLARKE3H_H__
