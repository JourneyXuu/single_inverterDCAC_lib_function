/* ==================================================================================
File name:  unbalance.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 计算电网不平衡系数

Target: TMS320F2833x family

=====================================================================================
History:
-------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
#ifndef __unbalance_H__
#define __unbalance_H__

typedef struct {  _iq  Ua;   //输入:网侧A相相电压有效值
				  _iq  Ub;   //输入:网侧B相相电压有效值
				  _iq  Uc;   //输入:网侧C相相电压有效值
				  _iq  L_num;//L表达式的分子部分
				  _iq  L_den;//L表达式的分母部分
				  _iq  L;    //中间变量L
				  _iq  e; 	 //输出：计算得的不平衡度
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } unbalance;	
                 
typedef unbalance *unbalance_handle;
                 
#define unbalance_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          1, \
						  0, \
						  0, \
              			  (void (*)(Uint32))unbalance_calc }

void unbalance_calc(unbalance_handle);

#endif 
