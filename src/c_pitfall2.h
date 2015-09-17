/*

 Pitfall 2 8K bankswitch scheme -- similar to standard F8
*/

#ifndef __C_PITFALL2_H__
#define __C_PITFALL2_H__

#include "globals.h"

db P2_Flags[8];
dd P2_Counters[8];
db P2_Top[8];
db P2_Bottom[8];
db P2_Enable[8];
dd P2_Music_Top[8];
dd P2_Music_Bottom[8];
dd P2_Music_Count[8];

db P2_Rbyte;	 //  return value for CPU read commands
db P2_AUDV;		 //  create an AUDV byte here

dd P2_sreg;		 //  initialize shift register to non-zero val

/*
 sound mixing table
 convert 3 sound channel bits into an AUDV value
*/
db Mix_AUDV[8];

/*
	read commands
*/

void (* P2_ReadFunctions[0x40])(void);


/*
	write commands
*/

void (* P2_WriteFunctions[0x40])(void);



void P2_NoIO(void);
dd Tune_Music(void);
void P2_WriteTop(void);
void P2_WriteBottom(void);
void P2_WriteCounterLow(void);
void P2_WriteCounterHigh(void);
void P2_ResetRandom(void);
void P2_ReadFlags(void);
void Read_DF(void);
void P2_Read_DF(void);
void P2_Read_DF_Flag(void);
void P2_Read_Random(void);
void P2_Read_Sound(void);
void Clock_Music(void);
void Clock_Pitfall2(void);

/*
	Pitfall 2 initialization
*/

void Init_P2(void);
void SetPitfallII(void);
void InitP2(void);

#endif