/* ==================================================================================
File name:  unbalance.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: ���������ƽ��ϵ��

Target: TMS320F2833x family

=====================================================================================
History:
-------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
#ifndef __unbalance_H__
#define __unbalance_H__

typedef struct {  _iq  Ua;   //����:����A�����ѹ��Чֵ
				  _iq  Ub;   //����:����B�����ѹ��Чֵ
				  _iq  Uc;   //����:����C�����ѹ��Чֵ
				  _iq  L_num;//L���ʽ�ķ��Ӳ���
				  _iq  L_den;//L���ʽ�ķ�ĸ����
				  _iq  L;    //�м����L
				  _iq  e; 	 //���������õĲ�ƽ���
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
