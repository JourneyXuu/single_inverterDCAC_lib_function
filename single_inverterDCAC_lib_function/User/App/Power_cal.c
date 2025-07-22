/*=====================================================================================
 File name:       Power_cal.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription: Power_cal                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 06-09-2014	Version 1.0
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "Power_cal.h"
#include "parameter.h"
#include "math.h"
//#ifdef __cplusplus
//#pragma CODE_SECTION("Power_calc")
//#else
//#pragma CODE_SECTION(Power_calc,"Power_calcFile");
//#endif
void Power_calc(POWER_CALC *v)
{	 v->P_meas= v->UAlpha * v->IAlpha + v->UBeta * v->IBeta;
     v->Q_meas= v->UBeta * v->IAlpha - v->UAlpha * v->IBeta;
     v->P_meas=v->P_meas* 1.5;
     v->Q_meas=v->Q_meas * 1.5;
}
