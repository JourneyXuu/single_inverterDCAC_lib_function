/*=====================================================================================
 File name:        FLL.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription:  FLL Transformation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-4-2011	Version 1.00
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
#include "dmctype.h"
#include "FLL.h"

void FLL_angle_calc(FLL_cal *v)
{	
     _iq temp,temp1;

     temp = -1 * v->qu * v->delta_u * v->Ki;
     temp1 = v->last_integer + temp * v-> T;
     v->we = v->wff + temp1;
     v->last_integer = temp1;
     v->theata = v->theata + v->we * v-> T;

     if(v->theata > 3.14159265358979)
        {v->theata -= 6.28318530717958;}
     else if(v->theata < -3.14159265358979)
        {v->theata += 6.28318530717958;}
}
