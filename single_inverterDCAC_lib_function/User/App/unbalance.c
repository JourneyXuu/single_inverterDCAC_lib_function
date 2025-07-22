/*=====================================================================================
 File name:        unbalance.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  calculate the unbalance  coefficient(计算不平衡系数)                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 08-30-2012	Version 1.00
-------------------------------------------------------------------------------------*/
#include "IQmathLib.h"         
#include "dmctype.h"
#include "unbalance.h"
#include <math.h>

void unbalance_calc(unbalance *v)
{
	v->L_num = v->Ua * v->Ua * v->Ua * v->Ua + v->Ub * v->Ub * v->Ub * v->Ub + v->Uc * v->Uc * v->Uc * v->Uc;
	v->L_den = (v->Ua * v->Ua + v->Ub * v->Ub + v->Uc * v->Uc) * (v->Ua * v->Ua + v->Ub * v->Ub + v->Uc * v->Uc);
	v->L = v->L_num / v->L_den;
	v->e = sqrt((1 - sqrt(3 - 6 * v->L)) / (1 + sqrt(3 - 6 * v->L)));
}
