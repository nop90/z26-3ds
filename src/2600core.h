/*

	2600core.c -- c_emulator() main entry point here...

*/

#ifndef __2600CORE_H__
#define __2600CORE_H__

/*
void do_Instruction_line(void);
void SetStarpath(void);
void SetPitfallII(void);
*/

void BlankBufferEnd(void);
void ScanFrame();
void Reset_emulator(void);
void c_emulator(void);

#endif

/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  
 z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/
