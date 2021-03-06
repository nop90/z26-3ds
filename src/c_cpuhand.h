/*

	cpu memory and register handlers -- used by the CPU emulator


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#ifndef __C_CPUHAND_H__
#define __C_CPUHAND_H__

void Init_CPUhand();
void ReadHardware(void);
void WriteHardware(void);

#endif