/*=====================================================================================
 File name:        RAMPGEN.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Ramp Generation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 07-22-2011	Version 1.00
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "rampgen.h"
#include "parameter.h"
#include <math.h>

void rampgen_calc(RAMPGEN *v)
{	
     _iq U_step;
// Compute the angle rate
        v->Angle += v->StepAngleMax;       
       
        if (v->Angle > (2 * PI))
          v->Angle -= (2 * PI);
//¼ÆËãÐ±ÆÂÉÏÉý¸´ÖÆ
       U_step=v->Umax * 0.0002 * v->T_step;
	   v->U +=U_step;
	   if (v->U>v->Umax)
	     v->U=v->Umax;
// Compute the ramp output
       v->Sine = v->U*sin(v->Angle);
	   v->Cosine = v->U*cos(v->Angle);
}

