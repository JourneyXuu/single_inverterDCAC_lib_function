/*=====================================================================================
 File name:        RMP_CNTL.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  The Ramp Control                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "rmp_cntl.h"


void rmp_cntl_calc(RMPCNTL *v)
{	
     _iq tmp;
       
     tmp = v->TargetValue - v->SetpointValue;
     
      if (tmp < 0)
      {
         v->RampDelayCount += 1;
         if (v->RampDelayCount >= v->RampDelayMax)
         {
            v->SetpointValue = v->SetpointValue - 1;       
            if (v->SetpointValue < v->RampHighLimit)
              v->SetpointValue = v->RampHighLimit;           
            v->RampDelayCount = 0;
         }        
      }
}


