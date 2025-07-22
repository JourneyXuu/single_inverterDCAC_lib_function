/* =================================================================================
File name:      Xian_Xiang.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the Xian_Xiang.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                  
------------------------------------------------------------------------------*/
#ifndef __Xian_Xiang_H__
#define __Xian_Xiang_H__

typedef struct {  _iq  Uab;  		//  xiandianya Uab
				  _iq  Ubc;	  	// xiandianya Ubc
				  _iq  Uca;	  	// xiandianya Uca 
				  _iq  Ua;			// xiangdianya Ua 
				  _iq  Ub;			// xiangdianya Ub 
                  _iq  Uc;           	// xiangdianya Uc 
		 	 	  void (*calc)();	  	// Pointer to calculation function
				 } XIANXIANG;	            

typedef XIANXIANG *Xian_Xiang_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the Xian_Xiang object.
-----------------------------------------------------------------------------*/                     
#define Xian_Xiang_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
						   0, \
              			  (void (*)(Uint32))Xian_Xiang_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in Xian_Xiang.C
------------------------------------------------------------------------------*/
void Xian_Xiang_calc(Xian_Xiang_handle);

#endif // __Xian_Xiang_H__
