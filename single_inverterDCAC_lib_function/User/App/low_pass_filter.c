/*---------------------------------------------
设置低通滤波器参数K1，K2
 K1=tao/（tao+T）  K2=T/(tao+T)  tao=1/(2*pi*fc)  其中fc为截止频率，T为采样频率  
 取截止频率为50Hz，采样频率为5KHz，tao =0.003183098    
---------------------------------------------*/

#include "IQmathLib.h"         
#include "dmctype.h"
#include "low_pass_filter.h"

void low_pass_filter_calc(LOW_PASS_FILTER *p)
{

	_iq Tmp1;

	Tmp1 = _IQmpy(p->K1,p->out)+_IQmpy(p->K2,p->in); 
    p->out=Tmp1;

}
