/*

 Starpath Supercharger support for z26

*/

#ifndef __C_STARPATH_H__
#define __C_STARPATH_H__

#include "globals.h"

dd SP_Scheme[8][2];

dd SPSlice[2];

dd SP_PrevAdr;

db SP_RamByte;

db SP_WriteEnable;
db SP_AddressCount;


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

#endif

/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/
