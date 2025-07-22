/*=====================================================================================
 File name:        Xian_Xiang.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Alphascription:  Xian_Xiang Transformation                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "IQmathLib.h"         // Include header for IQmath library
// Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file
#include "dmctype.h"
#include "Xian_Xiang.h"

//xian voltages invert to xiang voltages

void Xian_Xiang_calc(XIANXIANG *v)
{	
     //v->Ua=_IQdiv(_IQmpy(_IQ(2),v->Uab)+v->Ubc,_IQ(3));

     v->Ua=_IQdiv(v->Uab-v->Uca,_IQ(3));
     v->Ub=_IQdiv(v->Ubc-v->Uab,_IQ(3));
	 v->Uc=_IQdiv(v->Uca-v->Ubc,_IQ(3));
 
}
