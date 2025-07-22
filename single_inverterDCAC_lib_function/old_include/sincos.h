/* =================================================================================
File name:       sine/cosine=sincos.H   (IQ version)                  
                    
Originator:	calculator the sine/cosine value base on the Alpha/Beta

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the sincos.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                  
------------------------------------------------------------------------------*/
#ifndef __SINCOS_H__
#define __SINCOS_H__

typedef struct {  _iq  Alpha;  		// Input: stationary d-axis stator variable
				  _iq  Beta;		// Input: stationary q-axis stator variable
				  _iq  Sine;		// Output:sin signals
				  _iq  Cosine;       //Output:cos signals
		 	 	  void  (*calc)();	// Pointer to calculation function 
				 } SINCOS;	            

typedef SINCOS *SINCOS_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SINCOS object.
-----------------------------------------------------------------------------*/                     
#define SINCOS_DEFAULTS {  0, \
                          0, \
                          0, \
						  1, \
              			  (void (*)(Uint32))sincos_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SINCOS.C
------------------------------------------------------------------------------*/
extern void sincos_calc(SINCOS_handle);

#endif // __SINCOS_H__

