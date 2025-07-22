#include "IQmathLib.h"         // Include header for IQmath library
#include "dmctype.h"
#include "dtime_comp.h"
#include "math.h"


void dt_comp_calc(DT_COMP * p)
{	
   _iq var1,var2;
    
//**********求电流矢量角*****************
	var1 =  _IQatan2(p->Iqs,p->Ids);

	if(p->Iqs >0)
		{
			if(p->Ids >0)
				var1 = var1;
			else
				var1 = var1 + 3.141592654;
		}
	else
		{
			if(p->Ids >0)
				var1 = var1;
			else
				var1 = var1 - 3.141592654;
		}

	var1 += p->Angle;
	if(var1>_IQ(3.141592654))
	  p->Angle_I= var1 -_IQ(6.283185308); 
	else
	  p->Angle_I = var1;

//*****计算补偿值 4*Udc*Td/(3*Ts),幅值利用 Udc/sqr(3) 标幺化******
    var2 = _IQdiv((_IQ(p->Td)),_IQ(0.0002)); //Td/T
    var2 = _IQmpy(_IQ(2.309401),var2);        // 4/saq(3)

//********* 根据不同扇区求解补偿值*******************
    if(p->Angle_I<=_IQ(0.523598775) && p->Angle_I>_IQ(-0.523598775))       
	  {
	     //p->sector=1;
		 p->comp_alfa = var2;
		 p->comp_beta = 0;         
	       
	  }
	else if (p->Angle_I<=_IQ(1.570796327) && p->Angle_I>_IQ(0.523598775))     
	  {
	    // p->sector=2;
		 p->comp_alfa = _IQmpy(_IQ(0.5),var2);		
         p->comp_beta = _IQmpy(_IQ(0.866667),var2);
	  
	  }
    else if (p->Angle_I<=_IQ(2.617993878) && p->Angle_I>_IQ(1.570796327)) 
	  {
	    // p->sector=3;
		 p->comp_alfa = _IQmpy(_IQ(-0.5),var2);		
         p->comp_beta = _IQmpy(_IQ(0.866667),var2);
	  
	  }
    else if ((p->Angle_I<=_IQ(3.141592654) && p->Angle_I>_IQ(2.617993878)) || (p->Angle_I<=_IQ(-2.617993878) && p->Angle_I>=_IQ(-3.141592654))) 
	  {
	    // p->sector=4;
		 p->comp_alfa = _IQmpy(_IQ(-1),var2);		
         p->comp_beta = 0;
	  
	  }
    else if (p->Angle_I>_IQ(-2.617993878) && p->Angle_I<=_IQ(-1.570796327))     
	  {
	    // p->sector=5;			  
		 p->comp_alfa = _IQmpy(_IQ(-0.5),var2);		
         p->comp_beta = _IQmpy(_IQ(-0.866667),var2);
	  
	  }
	else  
	  {
	    // p->sector=6;		
		 p->comp_alfa = _IQmpy(_IQ(0.5),var2);		
         p->comp_beta = _IQmpy(_IQ(-0.866667),var2);
	  
	  }

}


