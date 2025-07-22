/*=====================================================================================
 File name:        PARK.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription:  Park Transformation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "park.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void park_calc(PARK *v)
{	
  
    _iq Cosine,Sine;

// Using look-up IQ sine table
     Sine =sin(v->Angle);
     Cosine =cos(v->Angle);

     v->Ds = _IQmpy(v->Alpha,Cosine) + _IQmpy(v->Beta,Sine);
     v->Qs = _IQmpy(v->Beta,Cosine) - _IQmpy(v->Alpha,Sine);

}


