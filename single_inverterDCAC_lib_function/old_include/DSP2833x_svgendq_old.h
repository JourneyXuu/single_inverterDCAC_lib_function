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
/* 传统sv
typedef struct  { _iq  Ualpha;          // Input: reference alpha-axis phase voltage
                  _iq  Ubeta;           // Input: reference beta-axis phase voltage
                  _iq  Ta;              // Output: reference phase-a switching function
                  _iq  Tb;              // Output: reference phase-b switching function
                  _iq  Tc;              // Output: reference phase-c switching function
                  void (*calc)();       // Pointer to calculation function
                } SVGENDQ;
*/
typedef struct  { _iq  Vg;          // 电网电压有效值
                  _iq  Vpv;           // 光伏输出电压
                  _iq  SinT;              // 输入正弦角度
                  _iq  Ig;              // 输出电流指令的有效值
                  _iq  Tr;              // 谐振时间
                  _iq  Lp;              // 励磁电感
                  _iq  NT;              // 匝比
                  _iq  Tpwm;              // PWM周期
                  _iq  Dout;              // PWM占空比
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
