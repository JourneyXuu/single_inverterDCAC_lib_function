/* =================================================================================
File name:      BPF.H (Float version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the Band_pass Filter.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 12-14-2013	Version 1.00                                                  
------------------------------------------------------------------------------*/
#ifndef __BPF_H__
#define __BPF_H__

typedef struct {  _iq  A;  		//Parameter:Gain for BPF 
				  _iq  wc;	  	//Parameter:Cutoff Frequence for BPF
				  _iq  w0;	  	// Parameter:Center Frequence for BPF
				  _iq  Ts;	  	// Parameter:Sample Frequence
				  _iq  Uk;		//Input: Uk
				  _iq  Uk_1;	//Input: Uk_1
				  _iq  Uk_2;	//Input: Uk_2
				  _iq  Yk;		//Input: Yk
				  _iq  Yk_1;	//Input: Yk_1
				  _iq  Yk_2;	//Input: Yk_2
		 	 	  void (*calc)();	  	// Pointer to calculation function
				 } BandPass_Filter;	            

typedef BandPass_Filter *BPF_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the Xian_Xiang object.
-----------------------------------------------------------------------------*/                     
#define BPF_DEFAULTS {0, \
                           0, \
                           0, \
                           0, \
                           0, \
						   0, \
						   0, \
						   0, \
						   0, \
						   0, \
              			  (void (*)(Uint32))BPF_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in Xian_Xiang.C
------------------------------------------------------------------------------*/
void BPF_calc(BPF_handle);

#endif // __BPF_H__
