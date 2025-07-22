/* ==============================================================================
System Name:  ACI33

File Name:	PARAMETER.H

Description:	Parameters file for the Sensored Indirect Field
          	    Orientation Control for a Three Phase AC Induction Motor. 

Originator:		Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be DMC1500 board.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
=================================================================================  */

#ifndef PARAMETER_H
#define PARAMETER_H



/*-------------------------------------------------------------------------------
Next, definitions used in main file.
-------------------------------------------------------------------------------*/
#ifndef TRUE
#define FALSE 0
#define TRUE  1
#endif

#define PI 3.14159265358979


#define SYSTEM_FREQUENCY 150


// Define the ISR frequency (kHz)
#define ISR_FREQUENCY 5


// Define the base quantites
#define BASE_VOLTAGE    184.752       // Base peak phase voltage (volt)
#define BASE_CURRENT    5             // Base peak phase current (amp)
#define BASE_TORQUE     1.3    // Base torque (N.m)
#define BASE_FLUX       0.9       // Base flux linkage (volt.sec/rad)
#define BASE_FREQ      	50            // Base electrical frequency (Hz)

#endif  // end of PARAMETER.H definition

//===========================================================================
// No more.
//===========================================================================
