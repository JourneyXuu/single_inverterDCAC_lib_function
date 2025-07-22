/*=====================================================================================
 File name:        Cal_sincos.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Dsscription:  calculator sin/cos value                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 07-22-2011	Version 1.00
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "sincos.h"
#include <math.h>

void sincos_calc(SINCOS *v)
{	    
     v->Sine = v->Beta / sqrt(v->Alpha * v->Alpha + v->Beta * v->Beta);
     v->Cosine = v->Alpha / sqrt(v->Alpha * v->Alpha + v->Beta * v->Beta);  
}
