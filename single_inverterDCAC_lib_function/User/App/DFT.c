/*=====================================================================================
 File name:        DFT.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription:  DFT Calculate                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 3-8-2012	Version 1.00
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
#include "dmctype.h"
#include "parameter.h"
#include "DFT.h"
#include <math.h>

void DFT_Calculate(DFT_Cal *v)
{	

	 v->Real_number = v->Real_number + v->Signal_In * cos((2 * PI * v->H * v->Counter_n)/v->N );
	 v->Imag_number = v->Imag_number + v->Signal_In * sin((2 * PI * v->H * v->Counter_n)/v->N );
	 v->Counter_n = v->Counter_n + 1;
	 if(v->Counter_n == v->N)
	  {
	  	v->Counter_n = 0;
		v->Real_number = v->Real_number * 2 / v->N;
		v->Imag_number = v->Imag_number * 2 / v->N;
        v->RMS = _IQmag(v->Real_number,v->Imag_number) / 1.41421356;
		v->Real_number = 0;
		v->Imag_number = 0;
	  }
}
