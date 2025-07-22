/*=====================================================================================
 File name:        CLARKE3.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Clarke3 Transformation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "3hclarke.h"
#ifdef __cplusplus
#pragma CODE_SECTION("clarke3h_calcFile")
#else
#pragma CODE_SECTION(clarke3h_calc,"clarke3h_calcFile");
#endif
void clarke3h_calc(CLARKE3H *v)
{	

   v->Alpha =  _IQmpy(_IQmpy(_IQ(2),v->As)-v->Bs-v->Cs,_IQ(0.33333333333333));//(2As-Bs-Cs)/3

   v->Beta = _IQmpy((v->Bs - v->Cs),_IQ(0.57735026918963)); // 1/sqrt(3) = 0.57735026918963
 
}
