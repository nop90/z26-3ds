/*
	z26 RIOT emu

	I'm not really sure what mode the timer starts up in but it's not mode 1.
	Otherwise blueprnt.bin doesn't come up and others as well.
*/

#pragma once

#include "globals.h"

#define START_TIME 0x7fff

dd Timer = START_TIME;	//  the RIOT Timer
						// (gets initialized in INIT.C now)

void (* TimerReadVec)(void);	//  timer read vector

db DDR_A = 0;
db DDR_B = 0;


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

void (* ReadRIOTTab[8])(void) = {						
	ReadPortA,			//  280h PA Data
	ReadDDR_A,			//  281h PA Direction
	ReadPortB,			//  282h PB Data
	ReadDDR_B,			//  283h PB Direction
	ReadTimer,			//  284h Read Timer
	ReadTimerIntReg,	//  285h Read Timer Interrupt Register
	ReadTimer,			//  286h Read Timer
	ReadTimerIntReg		//  287h Read Timer Interrupt Register
};

void (* WriteRIOTTab[4])(void) = {
	SetRIOTTimer1,		//  294h
	SetRIOTTimer8,		//  295h
	SetRIOTTimer64,		//  296h
	SetRIOTTimer1024	//  297h
};

void (* WriteRIOTTab2[4])(void) = {
	WritePortA,		//  280h
	WriteDDR_A,		//  281h
	WriteNothing,	//  282h
	WriteDDR_B		//  283h
};


void Init_Riot(void);
void ReadRIOT(void);
void WriteRIOT(void);
void  ClockRIOT(void);

void (* WriteRIOTHandler[32])(void) = {
	WritePortA,		//  280h
	WriteDDR_A,		//  281h
	WriteNothing,	//  282h
	WriteDDR_B,		//  283h
	WriteNothing,
	WriteNothing,
	WriteNothing,
	WriteNothing,

	WritePortA,		//  280h
	WriteDDR_A,		//  281h
	WriteNothing,	//  282h
	WriteDDR_B,		//  283h
	WriteNothing,
	WriteNothing,
	WriteNothing,
	WriteNothing,

	WritePortA,		//  280h
	WriteDDR_A,		//  281h
	WriteNothing,	//  282h
	WriteDDR_B,		//  283h
	SetRIOTTimer1,		//  294h
	SetRIOTTimer8,		//  295h
	SetRIOTTimer64,		//  296h
	SetRIOTTimer1024,	//  297h

	WritePortA,		//  280h
	WriteDDR_A,		//  281h
	WriteNothing,	//  282h
	WriteDDR_B,		//  283h
	SetRIOTTimer1,		//  294h
	SetRIOTTimer8,		//  295h
	SetRIOTTimer64,		//  296h
	SetRIOTTimer1024	//  297h
};

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).  
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
