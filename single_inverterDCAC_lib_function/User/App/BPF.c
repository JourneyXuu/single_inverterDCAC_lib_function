/*=====================================================================================
 File name:       BPF.C (Float version)                 
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription: Band_pass Filter                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 12-14-2013	Version 1.00  
-------------------------------------------------------------------------------------*/
#include "IQmathLib.h"         // Include header for IQmath library
#include "dmctype.h"
#include "BPF.h"
#include <math.h>

void BPF_calc(BandPass_Filter *v)
{	
     _iq u2,u0,y2,y1,y0,C,a1,a2;
//calculater the parameter for the decrete from the continues
     C= v->w0 / tan(v->w0 * v->Ts / 2);
	 u2=- v->A * v->wc * C;
	 u0=v->A * v->wc * C;
	 y2=C * C + v->w0 * v->w0 - v->wc * C;
	 y1=2 * v->w0 * v->w0 - 2 * C * C;
	 y0=C * C + v->w0 * v->w0 + v->wc * C;

	 a1=v->Uk * u0 + v->Uk_2 * u2;
	 a2=v->Yk_2 * y2 + v->Yk_1 * y1;
	 v->Yk=(a1-a2)/y0;
	 v->Yk_2=v->Yk_1;
	 v->Yk_1=v->Yk;
	 v->Uk_2=v->Uk_1;
	 v->Uk_1=v->Uk;
}
