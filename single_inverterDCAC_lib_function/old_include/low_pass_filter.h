/* =================================================================================
File name:low_pass_filter          
                    
Originator:

Description: 
      低通滤波器头文件，low_pass_filter.c
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 28-02-2010        
  fout（k）=K1*fout（k-1）+K2*Win  
  K1=tao/（tao+T）  K2=T/(tao+T)  tao=1/(2*pi*fc)  其中fc为截止频率，T为采样频率
  
  取截止频率为50Hz，采样频率为5KHz，tao =0.003183098                                  
------------------------------------------------------------------------------*/
#ifndef __LOW_PASS_FILTER__
#define __LOW_PASS_FILTER__

typedef struct {
      
       _iq in;        // 滤波器输入
       _iq out;       //滤波器输出
	   _iq Uplimt;
	   _iq Downlimt;
       _iq K1;         		// 参数k1  fout（k）=K1*fout（k-1）+K2*Win
       _iq K2;         		// Parameter: Constant for low-pass filter       
       void (*calc)();  	// Pointer to the calulation function
       } LOW_PASS_FILTER;   	// Data type created

typedef LOW_PASS_FILTER *LOW_PASS_FILTER_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_QEP object.
-----------------------------------------------------------------------------*/                     
#define LOW_PASS_FILTER_DEFAULTS   {0,\
                                    0,\
                                    0,0,\
                                    0,0,\
                                    (void (*)(Uint32))low_pass_filter_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_FR.C
------------------------------------------------------------------------------*/
void low_pass_filter_calc(LOW_PASS_FILTER_handle); 

#endif // _LOW_PASS_FILER__
