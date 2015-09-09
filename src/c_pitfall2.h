/*

 Pitfall 2 8K bankswitch scheme -- similar to standard F8
*/

#pragma once

#include "globals.h"

db P2_Flags[8] = 		{ 0,0,0,0,0,0,0,0 };
dd P2_Counters[8] = 	{ 0,0,0,0,0,0,0,0 };
db P2_Top[8] = 			{ 0,0,0,0,0,0,0,0 };
db P2_Bottom[8] = 		{ 0,0,0,0,0,0,0,0 };
db P2_Enable[8] = 		{ 0,0,0,0,0,0,0,0 };
dd P2_Music_Top[8] = 	{ 0,0,0,0,0,0,0,0 };
dd P2_Music_Bottom[8] = { 0,0,0,0,0,0,0,0 };
dd P2_Music_Count[8] = 	{ 0,0,0,0,0,0,0,0 };

db P2_Rbyte = 0;	 //  return value for CPU read commands
db P2_AUDV = 0;		 //  create an AUDV byte here

dd P2_sreg = 0;		 //  initialize shift register to non-zero val

/*
 sound mixing table
 convert 3 sound channel bits into an AUDV value
*/
db Mix_AUDV[8] = { 0, 6, 5, 0xb, 4, 0xa, 9, 0xf};


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
	read commands
*/

void (* P2_ReadFunctions[0x40])(void) = {
	P2_Read_Random,		 //  00 -- Random # generator
	P2_Read_Random,		 //  01 -- Random # generator
	P2_Read_Random,		 //  02 -- Random # generator
	P2_Read_Random,		 //  03 -- Random # generator
	P2_Read_Sound,		 //  04 -- Sound value
	P2_Read_Sound,		 //  05 -- Sound value
	P2_Read_Sound,		 //  06 -- Sound value
	P2_Read_Sound,		 //  07 -- Sound value
	P2_Read_DF,			 //  08 -- DF0
	P2_Read_DF,			 //  09 -- DF1
	P2_Read_DF,			 //  0a -- DF2
	P2_Read_DF,			 //  0b -- DF3
	P2_Read_DF,			 //  0c -- DF4
	P2_Read_DF,			 //  0d -- DF5
	P2_Read_DF,			 //  0e -- DF6
	P2_Read_DF,			 //  0f -- DF7
	P2_Read_DF_Flag,	 //  10 -- DF0 AND flag
	P2_Read_DF_Flag,	 //  11 -- DF1 AND flag
	P2_Read_DF_Flag,	 //  12 -- DF2 AND flag
	P2_Read_DF_Flag,	 //  13 -- DF3 AND flag
	P2_Read_DF_Flag,	 //  14 -- DF4 AND flag
	P2_Read_DF_Flag,	 //  15 -- DF5 AND flag
	P2_Read_DF_Flag,	 //  16 -- DF6 AND flag
	P2_Read_DF_Flag,	 //  17 -- DF7 AND flag
	P2_NoIO,			 //  18 -- DF0 AND flag swapped
	P2_NoIO,			 //  19 -- DF1 AND flag swapped
	P2_NoIO,			 //  1a -- DF2 AND flag swapped
	P2_NoIO,			 //  1b -- DF3 AND flag swapped
	P2_NoIO,			 //  1c -- DF4 AND flag swapped
	P2_NoIO,			 //  1d -- DF5 AND flag swapped
	P2_NoIO,			 //  1e -- DF6 AND flag swapped
	P2_NoIO,			 //  1f -- DF7 AND flag swapped
	P2_NoIO,			 //  20 -- DF0 AND flag reversed
	P2_NoIO,			 //  21 -- DF1 AND flag reversed
	P2_NoIO,			 //  22 -- DF2 AND flag reversed
	P2_NoIO,			 //  23 -- DF3 AND flag reversed
	P2_NoIO,			 //  24 -- DF4 AND flag reversed
	P2_NoIO,			 //  25 -- DF5 AND flag reversed
	P2_NoIO,			 //  26 -- DF6 AND flag reversed
	P2_NoIO,			 //  27 -- DF7 AND flag reversed
	P2_NoIO,			 //  28 -- DF0 AND flag SHR 1
	P2_NoIO,			 //  29 -- DF1 AND flag SHR 1
	P2_NoIO,			 //  2a -- DF2 AND flag SHR 1
	P2_NoIO,			 //  2b -- DF3 AND flag SHR 1
	P2_NoIO,			 //  2c -- DF4 AND flag SHR 1
	P2_NoIO,			 //  2d -- DF5 AND flag SHR 1
	P2_NoIO,			 //  2e -- DF6 AND flag SHR 1
	P2_NoIO,			 //  2f -- DF7 AND flag SHR 1
	P2_NoIO,			 //  30 -- DF0 AND flag SHL 1
	P2_NoIO,			 //  31 -- DF1 AND flag SHL 1
	P2_NoIO,			 //  32 -- DF2 AND flag SHL 1
	P2_NoIO,			 //  33 -- DF3 AND flag SHL 1
	P2_NoIO,			 //  34 -- DF4 AND flag SHL 1
	P2_NoIO,			 //  35 -- DF5 AND flag SHL 1
	P2_NoIO,			 //  36 -- DF6 AND flag SHL 1
	P2_NoIO,			 //  37 -- DF7 AND flag SHL 1
	P2_ReadFlags,		 //  38 -- DF0 flag
	P2_ReadFlags,		 //  39 -- DF1 flag
	P2_ReadFlags,		 //  3a -- DF2 flag
	P2_ReadFlags,		 //  3b -- DF3 flag
	P2_ReadFlags,		 //  3c -- DF4 flag
	P2_ReadFlags,		 //  3d -- DF5 flag
	P2_ReadFlags,		 //  3e -- DF6 flag
	P2_ReadFlags		 //  3f -- DF7 flag
};


/*
	write commands
*/

void (* P2_WriteFunctions[0x40])(void) = {
	P2_WriteTop,		 //  40 -- DF0 top count
	P2_WriteTop,		 //  41 -- DF1 top count
	P2_WriteTop,		 //  42 -- DF2 top count
	P2_WriteTop,		 //  43 -- DF3 top count
	P2_WriteTop,		 //  44 -- DF4 top count
	P2_WriteTop,		 //  45 -- DF5 top count
	P2_WriteTop,		 //  46 -- DF6 top count
	P2_WriteTop,		 //  47 -- DF7 top count
	P2_WriteBottom,		 //  48 -- DF0 bottom count
	P2_WriteBottom,		 //  49 -- DF1 bottom count
	P2_WriteBottom,		 //  4a -- DF2 bottom count
	P2_WriteBottom,		 //  4b -- DF3 bottom count
	P2_WriteBottom,		 //  4c -- DF4 bottom count
	P2_WriteBottom,		 //  4d -- DF5 bottom count
	P2_WriteBottom,		 //  4e -- DF6 bottom count
	P2_WriteBottom,		 //  4f -- DF7 bottom count
	P2_WriteCounterLow,	 //  50 -- DF0 counter low
	P2_WriteCounterLow,	 //  51 -- DF1 counter low
	P2_WriteCounterLow,	 //  52 -- DF2 counter low
	P2_WriteCounterLow,	 //  53 -- DF3 counter low
	P2_WriteCounterLow,	 //  54 -- DF4 counter low
	P2_WriteCounterLow,	 //  55 -- DF5 counter low
	P2_WriteCounterLow,	 //  56 -- DF6 counter low
	P2_WriteCounterLow,	 //  57 -- DF7 counter low
	P2_WriteCounterHigh, //  58 -- DF0 counter high
	P2_WriteCounterHigh, //  59 -- DF1 counter high
	P2_WriteCounterHigh, //  5a -- DF2 counter high
	P2_WriteCounterHigh, //  5b -- DF3 counter high
	P2_WriteCounterHigh, //  5c -- DF4 counter high
	P2_WriteCounterHigh, //  5d -- DF5 counter high AND music enable
	P2_WriteCounterHigh, //  5e -- DF6 counter high AND music enable
	P2_WriteCounterHigh, //  5f -- DF7 counter high AND music enable
	P2_NoIO,			 //  60 -- not used (draw line movement)
	P2_NoIO,			 //  61 -- not used (draw line movement)
	P2_NoIO,			 //  62 -- not used (draw line movement)
	P2_NoIO,			 //  63 -- not used (draw line movement)
	P2_NoIO,			 //  64 -- not used (draw line movement)
	P2_NoIO,			 //  65 -- not used (draw line movement)
	P2_NoIO,			 //  66 -- not used (draw line movement)
	P2_NoIO,			 //  67 -- not used (draw line movement)
	P2_NoIO,			 //  68 -- not used
	P2_NoIO,			 //  69 -- not used
	P2_NoIO,			 //  6a -- not used
	P2_NoIO,			 //  6b -- not used
	P2_NoIO,			 //  6c -- not used
	P2_NoIO,			 //  6d -- not used
	P2_NoIO,			 //  6e -- not used
	P2_NoIO,			 //  6f -- not used
	P2_ResetRandom,		 //  70 -- random number generator reset
	P2_ResetRandom,		 //  71 -- random number generator reset
	P2_ResetRandom,		 //  72 -- random number generator reset
	P2_ResetRandom,		 //  73 -- random number generator reset
	P2_ResetRandom,		 //  74 -- random number generator reset
	P2_ResetRandom,		 //  75 -- random number generator reset
	P2_ResetRandom,		 //  76 -- random number generator reset
	P2_ResetRandom,		 //  77 -- random number generator reset
	P2_NoIO,			 //  78 -- not used
	P2_NoIO,			 //  79 -- not used
	P2_NoIO,			 //  7a -- not used
	P2_NoIO,			 //  7b -- not used
	P2_NoIO,			 //  7c -- not used
	P2_NoIO,			 //  7d -- not used
	P2_NoIO,			 //  7e -- not used
	P2_NoIO				 //  7f -- not used
};


/*
	Pitfall 2 initialization
*/

void Init_P2(void);
void SetPitfallII(void);
void InitP2(void);