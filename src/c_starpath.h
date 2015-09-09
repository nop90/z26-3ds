/*

 Starpath Supercharger support for z26

*/

#pragma once

#include "globals.h"

dd SP_Scheme[8][2] = { /* table of bankswitch schemes */
	{2 * 0x800,	3 * 0x800},
	{0 * 0x800,	3 * 0x800},
	{2 * 0x800,	0 * 0x800},
	{0 * 0x800,	2 * 0x800},
	{2 * 0x800,	3 * 0x800},
	{1 * 0x800,	3 * 0x800},
	{2 * 0x800,	1 * 0x800},
	{1 * 0x800,	2 * 0x800}
};

dd SPSlice[2] = { 0, 3 * 0x800 };

dd SP_PrevAdr = 0;

/* byte(s) to write to RAM: */
db SP_RamByte = 0;

//db Starpath = 0;
db SP_WriteEnable = 0;
db SP_AddressCount = 7;


/*
	Starpath initialization
*/

void Init_Starpath(void);

void SP_SetScheme(void);

void SetStarpath(void);

void ShowJAMmessage(void);

void StarpathLoadNotFound(void);

void StarpathRealJAM(void);

void StarpathJAM(void);

void SP_Q_Adr(void);

void ReadSPlow(void);

void WriteSPlow(void);

void ReadSPhigh(void);

void WriteSPhigh(void);

void InitSP(void);

void RBank_SP(void);

void WBank_SP(void);


/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/
