/*

	6507 CPU emulator for z26


 This C file gets generated from cpu.m4, so please edit it there.

 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#ifndef __C_CPU_H__
#define __C_CPU_H__

void Init_CPU(void);
void Reset(void);
void do_Instruction(void);
void do_Instruction_line(void);

#endif