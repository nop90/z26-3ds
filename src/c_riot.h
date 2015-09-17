/*
	z26 RIOT emu

	I'm not really sure what mode the timer starts up in but it's not mode 1.
	Otherwise blueprnt.bin doesn't come up and others as well.
*/

#ifndef __C_RIOT_H__
#define __C_RIOT_H__

#include "globals.h"

#define START_TIME 0x7fff

dd Timer;	//  the RIOT Timer
						// (gets initialized in INIT.C now)
db DDR_A ;
db DDR_B;


void (* ReadRIOTTab[8])(void);

void (* WriteRIOTTab[4])(void);

void (* WriteRIOTTab2[4])(void);


void (* WriteRIOTHandler[32])(void);

void (* TimerReadVec)(void);	//  timer read vector

void Init_Riot(void);
void ReadRIOT(void);
void WriteRIOT(void);
void  ClockRIOT(void);

void WriteRIOTRAM(void);
void ReadRIOTRAM(void);
void ReadDDR_A(void);
void ReadDDR_B(void);
void ReadPortB(void);
void ReadPortA(void);
void WriteNothing(void);
void WritePortA(void);
void WriteDDR_A(void);
void WriteDDR_B(void);
void ReadTimer1(void);
void ReadTimer8(void);
void ReadTimer64(void);
void ReadTimer1024(void);
void ReadTimer(void);
void ReadTimerIntReg(void);
void SetRIOTTimer1(void);
void SetRIOTTimer8(void);
void SetRIOTTimer64(void);
void SetRIOTTimer1024(void);
void RandomizeRIOTTimer();

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).  
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
