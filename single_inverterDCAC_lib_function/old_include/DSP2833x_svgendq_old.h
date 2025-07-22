/* =================================================================================
File name:       SVGEN_DQ.H  (IQ version)                    
                    
Originator: Digital Control Systems Group
            Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the SVGEN_DQ.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005 Version 3.20
------------------------------------------------------------------------------*/
#ifndef __SVGEN_DQ_H__
#define __SVGEN_DQ_H__
/* ��ͳsv
typedef struct  { _iq  Ualpha;          // Input: reference alpha-axis phase voltage
                  _iq  Ubeta;           // Input: reference beta-axis phase voltage
                  _iq  Ta;              // Output: reference phase-a switching function
                  _iq  Tb;              // Output: reference phase-b switching function
                  _iq  Tc;              // Output: reference phase-c switching function
                  void (*calc)();       // Pointer to calculation function
                } SVGENDQ;
*/
typedef struct  { _iq  Vg;          // ������ѹ��Чֵ
                  _iq  Vpv;           // ��������ѹ
                  _iq  SinT;              // �������ҽǶ�
                  _iq  Ig;              // �������ָ�����Чֵ
                  _iq  Tr;              // г��ʱ��
                  _iq  Lp;              // ���ŵ��
                  _iq  NT;              // �ѱ�
                  _iq  Tpwm;              // PWM����
                  _iq  Dout;              // PWMռ�ձ�
                  void (*calc)();       // Pointer to calculation function
                } SVGENDQ;
typedef SVGENDQ *SVGENDQ_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENDQ object.
-----------------------------------------------------------------------------*/                     
#define SVGENDQ_DEFAULTS { 66,30,0,0.5,0.0000018,0.000003,6,0.00005,0, \
                       (void (*)(Uint32))svgendq_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SVGEN_DQ.C
------------------------------------------------------------------------------*/
void svgendq_calc(SVGENDQ_handle);

#endif // __SVGEN_DQ_H__
