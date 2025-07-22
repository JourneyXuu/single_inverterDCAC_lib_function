/*=====================================================================================
 File name:        IPARK.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Dsscription:  Inverse Park Transformation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "ipark.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void ipark_calc(IPARK *v)
{	
   
   _iq Cosine,Sine;
   
// Using look-up IQ sine table
     Sine = sin(v->Angle);
     Cosine = cos(v->Angle);
 
     v->Alpha = _IQmpy(v->Ds,Cosine) - _IQmpy(v->Qs,Sine);
     v->Beta = _IQmpy(v->Qs,Cosine) + _IQmpy(v->Ds,Sine);  
}


