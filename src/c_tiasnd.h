/*

	tiasnd.c -- z26 sound generation routines

	based on TIASound (c) 1996-1997 by Ron Fries
	please see the end of this file for Ron's banner

*/

#pragma once

#include "globals.h"

/* CONSTANT DEFINITIONS */

/* definitions for AUDCx (15, 16) */
#define SET_TO_1     0x00      /* 0000 */
#define POLY4        0x01      /* 0001 */
#define DIV31_POLY4  0x02      /* 0010 */
#define POLY5_POLY4  0x03      /* 0011 */
#define PURE1        0x04      /* 0100 */
#define PURE2        0x05      /* 0101 */
#define DIV31_PURE   0x06      /* 0110 */
#define POLY5_2      0x07      /* 0111 */
#define POLY9        0x08      /* 1000 */
#define POLY5        0x09      /* 1001 */
#define DIV31_POLY5  0x0a      /* 1010 */
#define POLY5_POLY5  0x0b      /* 1011 */
#define DIV3_PURE    0x0c      /* 1100 */
#define DIV3_PURE2   0x0d      /* 1101 */
#define DIV93_PURE   0x0e      /* 1110 */
#define DIV3_POLY5   0x0f      /* 1111 */
                 
#define DIV3_MASK    0x0c                 
                 
#define AUDC0        0x15
#define AUDC1        0x16
#define AUDF0        0x17
#define AUDF1        0x18
#define AUDV0        0x19
#define AUDV1        0x1a

/* the size (in entries) of the 4 polynomial tables */
#define POLY4_SIZE  0x000f
#define POLY5_SIZE  0x001f
#define POLY9_SIZE  0x01ff

/* channel definitions */
#define CHAN1       0
#define CHAN2       1

#define FALSE       0
#define TRUE        1

int TSB_result;

/*
 Initialze the bit patterns for the polynomials.

 The 4bit and 5bit patterns are the identical ones used in the tia chip.
 Though the patterns could be packed with 8 bits per byte, using only a
 single bit per byte keeps the math simple, which is important for
 efficient processing.
*/

db Bit4[] = { 0,1,1,0,0,1,0,1,0,0,0,0,1,1,1 };
db Bit5[] = { 0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,1,0,1,0,0,1,1 };

/*
 1 = toggle output in 5 bit poly - used when poly5 clocks other outputs
*/

db Bit5T[] = { 1,0,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,0 };

/*
 The 'Div by 31' counter is treated as another polynomial because of
 the way it operates.  It does not have a 50% duty cycle, but instead
 has a 13:18 ratio (of course, 13+18 = 31).  This could also be
 implemented by using counters.
*/

db Div31[] = { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 };

db Div6[] = { 0,1,0,0,1,0 };

/*
 The sample output is treated as another divide by N counter.
 For better accuracy, the Samp_n_cnt has a fixed binary decimal point
 which has 8 binary digits to the right of the decimal point.
*/

dd Samp_n_cnt = 0;
dd Samp_n_max = 0;


db D6[] = { 0, 0 };
db P4[] = { 0, 0 };
db P5[] = { 0, 0 };
db AUDC[] = { 0, 0 };
db AUDF[] = { 0, 0 };
db AUDV[] = { 0, 0 };
db Outvol[] = { 0, 0 };
db Div_n_cnt[] = { 0, 0 };
db Div_n_max[] = { 0, 0 };

dd P9_sreg[] = { 1, 1 };
dd prev_sample = 0;
db next_sample = 0;


void TSB_Always_High(int chan);
	
void TSB_Poly4(int chan);
	
void TSB_Div31_Poly4(int chan);
	
void TSB_Poly5_Poly4(int chan);
	
void TSB_Pure(int chan);
	
void TSB_Div31_Pure(int chan);
	
void TSB_Poly5(int chan);
	
void TSB_Poly9(int chan);
	
void TSB_Poly5_Poly5(int chan);
	
void TSB_Div6_Pure(int chan);
	
void TSB_Div31_Div6(int chan);
	
void TSB_Poly5_Div6(int chan);
/*
AUDC_Jumptab:   ; dword           ; HEX  D3 D2 D1 D0    Clock Source    Clock Modifier    Source Pattern
		;                   --- -------------  --------------  ----------------  ----------------
        dd      TSB_Ch0done      ;   0    0  0  0  0    3.58 MHz/114 ->  none  (pure)  ->      none
        dd      TSB_Poly4        ;   1    0  0  0  1    3.58 MHz/114 ->  none  (pure)  ->   4-bit poly
        dd      TSB_Div31_Poly4  ;   2    0  0  1  0    3.58 MHz/114 ->  divide by 31  ->   4-bit poly
        dd      TSB_Poly5_Poly4  ;   3    0  0  1  1    3.58 MHz/114 ->   5-bit poly   ->   4-bit poly
        dd      TSB_Pure         ;   4    0  1  0  0    3.58 MHz/114 ->  none  (pure)  ->   pure  (~Q)
        dd      TSB_Pure         ;   5    0  1  0  1    3.58 MHz/114 ->  none  (pure)  ->   pure  (~Q)
        dd      TSB_Div31_Pure   ;   6    0  1  1  0    3.58 MHz/114 ->  divide by 31  ->   pure  (~Q)
;       dd      TSB_Poly5_Pure   ;   7    0  1  1  1    3.58 MHz/114 ->   5-bit poly   ->   pure  (~Q)
        dd      TSB_Poly5        ;   7    0  1  1  1    3.58 MHz/114 ->  none  (pure)  ->   5-bit poly
        dd      TSB_Poly9        ;   8    1  0  0  0    3.58 MHz/114 ->  none  (pure)  ->   9-bit poly
        dd      TSB_Poly5        ;   9    1  0  0  1    3.58 MHz/114 ->  none  (pure)  ->   5-bit poly
;       dd      TSB_Div31_Poly5  ;   A    1  0  1  0    3.58 MHz/114 ->  divide by 31  ->   5-bit poly
        dd      TSB_Div31_Pure   ;   A    1  0  1  0    3.58 MHz/114 ->  divide by 31  ->   pure  (~Q)
        dd      TSB_Poly5_Poly5  ;   B    1  0  1  1    3.58 MHz/114 ->   5-bit poly   ->   5-bit poly
        dd      TSB_Div6_Pure    ;   C    1  1  0  0    3.58 MHz/114 ->  divide by 6   ->   pure  (~Q)
        dd      TSB_Div6_Pure    ;   D    1  1  0  1    3.58 MHz/114 ->  divide by 6   ->   pure  (~Q)
        dd      TSB_Div31_Div6   ;   E    1  1  1  0    3.58 MHz/114 ->  divide by 31  ->   divide by 6
        dd      TSB_Poly5_Div6   ;   F    1  1  1  1    3.58 MHz/114 ->   5-bit poly   ->   divide by 6
*/

void (* AUDC_Jumptab[])(int chan) = {
	TSB_Always_High,
	TSB_Poly4,
	TSB_Div31_Poly4,
	TSB_Poly5_Poly4,
	TSB_Pure,
	TSB_Pure,
	TSB_Div31_Pure,
	TSB_Poly5,
	TSB_Poly9,
	TSB_Poly5,
	TSB_Div31_Pure,
	TSB_Poly5_Poly5,
	TSB_Div6_Pure,
	TSB_Div6_Pure,
	TSB_Div31_Div6,
	TSB_Poly5_Div6
};

void Init_Tiasnd();

void UTS_Chan(int chan);

void H_AUDC0();

void H_AUDC1();

void H_AUDF0();

void H_AUDF1();

void H_AUDV0();

void H_AUDV1();

void TSB_ProcessChannel(int chan);

void TSB_Ch0done();

dd TIA_Sound_Byte();

/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/
