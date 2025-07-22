/* =================================================================================
File name:        RAMPGEN.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
This file contains type definitions, constants and initializers for
the ramp generation functions contained in RAMPGEN.C
=====================================================================================
 History:
-------------------------------------------------------------------------------------
  07-22-2011	Version 1.00                                                 
------------------------------------------------------------------------------*/
#ifndef __RAMPGEN_H__
#define __RAMPGEN_H__

typedef struct {  	
		 	     _iq  StepAngleMax;	// Parameter: Maximum step angle 		
	 	 	     _iq  Angle;		// Variable: Step angle 					  
			     _iq  Sine;  	 	// Output: Ramp signal 
			     _iq  Cosine;	    // Output: Ramp signal
			     _iq  Umax;         //指令复制，斜坡上升时使用
			     _iq  T_step;
			     _iq  U;		 
	  	  	     void  (*calc)();	  	// Pointer to calculation function
			   } RAMPGEN;	            

typedef RAMPGEN *RAMPGEN_handle;  
/*------------------------------------------------------------------------------
      Object Initializers
------------------------------------------------------------------------------*/                       
#define RAMPGEN_DEFAULTS {0,0,0,0,0,0,0,\
                         (void (*)(Uint32))rampgen_calc }

/*------------------------------------------------------------------------------
      Funtion prototypes
------------------------------------------------------------------------------*/                                               
void rampgen_calc(RAMPGEN_handle);

#endif // __RAMPGEN_H__
