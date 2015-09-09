/*

	tialine.c -- generate a raster line


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#pragma once

#include "globals.h"

/* just to be able to compile with trace */
dd P0_Position = 0;
dd P1_Position = 0;
dd M0_Position = 0;
dd M1_Position = 0;
dd BL_Position = 0;


dd TIACollide = 0;	// state of the 15 collision bits

dd TIA_Last_Pixel = 0;	// remember how far we have rendered this line
db TIA_Display_HBlank = 0;	// show HMOVE bar in this line
dd TIA_HMOVE_Setup = 0;	// it takes several steps to setup an HMOVE
dd TIA_HMOVE_Clock = 16;	// how many HMOVE clocks since last HMOVE command
db TIA_HMOVE_Latches = 0;	// are we done with HMOVE pulses
db TIA_HMOVE_DoMove	= 0;	// do we need to apply more HMOVE pulses
/*
for continuity with TIA_Pixel_State:
P0 = 0x20
P1 = 0x10
M0 = 0x08
M1 = 0x04
BL = 0x02
*/
// how far to move object with HMOVE (0-15)
db TIA_HMP0_Value = 8;
db TIA_HMP1_Value = 8;
db TIA_HMM0_Value = 8;
db TIA_HMM1_Value = 8;
db TIA_HMBL_Value = 8;
db TIA_Pixel_State = 0;	// which objects to draw in this pixel (one bit each)
db TIA_Mask_Objects = 0x3f;	// enable VBLANK and let user disable objects
db TIA_Do_Output = 1;	// if line is offscreen, don't copy pixels to buffer
db CTRLPF_PF_Reflect = 0;	// reflect PF in right half of screen
db Current_PF_Pixel = 0;	// state of currently displayed PF pixel
// how wide are we supposed to display this pixel
db NUSIZ_P0_width = 0;
db NUSIZ_P1_width = 0;
db NUSIZ_M0_width = 0;
db NUSIZ_M1_width = 0;
db CTRLPF_BL_width = 0;
// reset missile to pixel 4 of player main copy
db TIA_RESMP0 = 0;
db TIA_RESMP1 = 0;
// use 'old' object data
db TIA_VDELP0 = 0;
db TIA_VDELP1 = 0;
db TIA_VDELBL = 0;
// reflect player
dd TIA_REFP0 = 0;
dd TIA_REFP1 = 0;
// graphics data for objects
dd TIA_GRP0_new = 0;
dd TIA_GRP0_old = 0;
dd TIA_GRP1_new = 0;
dd TIA_GRP1_old = 0;
dd TIA_ENAM0 = 0;
dd TIA_ENAM1 = 0;
dd TIA_ENABL_new = 0;
dd TIA_ENABL_old = 0;
// which object copies do we show
db NUSIZ0_number = 0;
db NUSIZ1_number = 0;
db CTRLPF_Score = 0;	// use score mode colours for playfield
db CTRLPF_Priority = 0;	// has playfield priority over movable objects
// object pixel counters for visible part of screen
dd TIA_P0_counter = 0;
dd TIA_P1_counter = 0;
dd TIA_M0_counter = 0;
dd TIA_M1_counter = 0;
dd TIA_BL_counter = 0;
// VBLANK, GRP0, GRP1, ENAM0, ENAM1, ENABL, REFP0, REFP1, PF0, PF1, PF2
// need one extra pixel for the write to take effect
// -> render one pixel ahead of counter before updating register state
db TIA_Delayed_Write = 0;

#define BG_COLOUR 0
#define PF_COLOUR 1
#define P1_COLOUR 2
#define P0_COLOUR 3

dw TIA_Colour_Table[4] = {0, 0, 0, 0};

db TIA_Priority_Table[2][64];
db TIA_Score_Priority_Table[2][64];

db ObjectStartTable[8][320];


dd TIA_P0_counter_reset = 0;
dd TIA_P1_counter_reset = 0;
dd TIA_M0_counter_reset = 0;
dd TIA_M1_counter_reset = 0;
dd TIA_BL_counter_reset = 0;

dd TIA_Playfield_Value = 0;
dd TIA_REFPF_Flag = 0;
db TIA_VBLANK = 0;

dw LoopCount;	// counter for the CatchUpPixels loop
dw CountLoop;

dd Pointer_Index_P0 = 0;
dd Pointer_Index_P1 = 0;
dd Pointer_Index_M0 = 0;
dd Pointer_Index_M1 = 0;
dd Pointer_Index_BL = 0;

db *TIA_P0_Line_Pointer;
db *TIA_P1_Line_Pointer;
db *TIA_M0_Line_Pointer;
db *TIA_M1_Line_Pointer;
db *TIA_BL_Line_Pointer;

db *TIA_P0_Table[0x2001];
db *TIA_P1_Table[0x2001];
db *TIA_M0_Table[0x81];
db *TIA_M1_Table[0x81];
db *TIA_BL_Table[9];

dd TIA_Playfield_Pixels[80] = {
	//repeated
	0x00100000, 0x00200000, 0x00400000, 0x00800000,	// PF0
	0x00008000, 0x00004000, 0x00002000, 0x00001000,	// PF1
	0x00000800, 0x00000400, 0x00000200, 0x00000100,	// PF1
	0x00000001, 0x00000002, 0x00000004, 0x00000008,	// PF2
	0x00000010, 0x00000020, 0x00000040, 0x00000080,	// PF2

	0x00100000, 0x00200000, 0x00400000, 0x00800000,	// PF0
	0x00008000, 0x00004000, 0x00002000, 0x00001000,	// PF1
	0x00000800, 0x00000400, 0x00000200, 0x00000100,	// PF1
	0x00000001, 0x00000002, 0x00000004, 0x00000008,	// PF2
	0x00000010, 0x00000020, 0x00000040, 0x00000080,	// PF2
	//reflected
	0x00100000, 0x00200000, 0x00400000, 0x00800000,	// PF0
	0x00008000, 0x00004000, 0x00002000, 0x00001000,	// PF1
	0x00000800, 0x00000400, 0x00000200, 0x00000100,	// PF1
	0x00000001, 0x00000002, 0x00000004, 0x00000008,	// PF2
	0x00000010, 0x00000020, 0x00000040, 0x00000080,	// PF2

	0x00000080, 0x00000040, 0x00000020, 0x00000010,	// PF2
	0x00000008, 0x00000004, 0x00000002, 0x00000001,	// PF2
	0x00000100, 0x00000200, 0x00000400, 0x00000800,	// PF1
	0x00001000, 0x00002000, 0x00004000, 0x00008000,	// PF1
	0x00800000, 0x00400000, 0x00200000, 0x00100000	// PF0
};
dd TIA_Playfield_Bits = 0;	// all 3 PF register values (0x00 PF0 PF1 PF2)

// where to draw missiles; used for generating the TIA_Mx_Tables
db Object_Table[8][4] = {
	{4,  0,  0,  0},
	{4, 20,  0,  0},
	{4,  0, 36,  0},
	{4, 20, 36,  0},
	{4,  0,  0, 68},
	{4,  0,  0,  0},
	{4,  0, 36, 68},
	{4,  0,  0,  0}
};

dw TIA_Collision_Table[64] = {
	0x0000, 0x0000, 0x0000, 0x2000, 0x0000, 0x0800, 0x0400, 0x2c00,
	0x0000, 0x0200, 0x0100, 0x2300, 0x4000, 0x4a00, 0x4500, 0x6f00,
	0x0000, 0x0080, 0x0040, 0x20c0, 0x0004, 0x0884, 0x0444, 0x2cc4,
	0x0002, 0x0282, 0x0142, 0x23c2, 0x4006, 0x4a26, 0x4546, 0x6f66,
	0x0000, 0x0020, 0x0010, 0x2030, 0x0008, 0x0828, 0x0418, 0x2c38,
	0x0001, 0x0221, 0x0111, 0x2331, 0x4009, 0x4a29, 0x4519, 0x6f39,
	0x8000, 0x80a0, 0x8050, 0xa0f0, 0x800c, 0x88ac, 0x845c, 0xacfc,
	0x8003, 0x82a3, 0x8153, 0xa3f3, 0xc00f, 0xcaaf, 0xc55f, 0xefff
};

/*
P0 P1 M0 M1 BL PF   P0P1 M0M1 BLPF ---- M1PF M1BL M0PF M0BL P1PF P1BL P0PF P0BL M1P0 M1P1 M0P1 M0P0
 0  0  0  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  0  0  0  0  1      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  0  0  0  1  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  0  0  0  1  1      0    0    1    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     2000

 0  0  0  1  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  0  0  1  0  1      0    0    0    0 .. 1    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0800
 0  0  0  1  1  0      0    0    0    0 .. 0    1    0    0 .. 0    0    0    0 .. 0    0    0    0     0400
 0  0  0  1  1  1      0    0    1    0 .. 1    1    0    0 .. 0    0    0    0 .. 0    0    0    0     2c00

 0  0  1  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  0  1  0  0  1      0    0    0    0 .. 0    0    1    0 .. 0    0    0    0 .. 0    0    0    0     0200
 0  0  1  0  1  0      0    0    0    0 .. 0    0    0    1 .. 0    0    0    0 .. 0    0    0    0     0100
 0  0  1  0  1  1      0    0    1    0 .. 0    0    1    1 .. 0    0    0    0 .. 0    0    0    0     2300

 0  0  1  1  0  0      0    1    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     4000
 0  0  1  1  0  1      0    1    0    0 .. 1    0    1    0 .. 0    0    0    0 .. 0    0    0    0     4a00
 0  0  1  1  1  0      0    1    0    0 .. 0    1    0    1 .. 0    0    0    0 .. 0    0    0    0     4500
 0  0  1  1  1  1      0    1    1    0 .. 1    1    1    1 .. 0    0    0    0 .. 0    0    0    0     6f00

 0  1  0  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 0  1  0  0  0  1      0    0    0    0 .. 0    0    0    0 .. 1    0    0    0 .. 0    0    0    0     0080
 0  1  0  0  1  0      0    0    0    0 .. 0    0    0    0 .. 0    1    0    0 .. 0    0    0    0     0040
 0  1  0  0  1  1      0    0    1    0 .. 0    0    0    0 .. 1    1    0    0 .. 0    0    0    0     20c0

 0  1  0  1  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    1    0    0     0004
 0  1  0  1  0  1      0    0    0    0 .. 1    0    0    0 .. 1    0    0    0 .. 0    1    0    0     0884
 0  1  0  1  1  0      0    0    0    0 .. 0    1    0    0 .. 0    1    0    0 .. 0    1    0    0     0444
 0  1  0  1  1  1      0    0    1    0 .. 1    1    0    0 .. 1    1    0    0 .. 0    1    0    0     2cc4

 0  1  1  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    1    0     0002
 0  1  1  0  0  1      0    0    0    0 .. 0    0    1    0 .. 1    0    0    0 .. 0    0    1    0     0282
 0  1  1  0  1  0      0    0    0    0 .. 0    0    0    1 .. 0    1    0    0 .. 0    0    1    0     0142
 0  1  1  0  1  1      0    0    1    0 .. 0    0    1    1 .. 1    1    0    0 .. 0    0    1    0     23c2

 0  1  1  1  0  0      0    1    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    1    1    0     4006
 0  1  1  1  0  1      0    1    0    0 .. 1    0    1    0 .. 0    0    1    0 .. 0    1    1    0     4a26
 0  1  1  1  1  0      0    1    0    0 .. 0    1    0    1 .. 0    1    0    0 .. 0    1    1    0     4546
 0  1  1  1  1  1      0    1    1    0 .. 1    1    1    1 .. 0    1    1    0 .. 0    1    1    0     6f66

 1  0  0  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     0000
 1  0  0  0  0  1      0    0    0    0 .. 0    0    0    0 .. 0    0    1    0 .. 0    0    0    0     0020
 1  0  0  0  1  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    1 .. 0    0    0    0     0010
 1  0  0  0  1  1      0    0    1    0 .. 0    0    0    0 .. 0    0    1    1 .. 0    0    0    0     2030

 1  0  0  1  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 1    0    0    0     0008
 1  0  0  1  0  1      0    0    0    0 .. 1    0    0    0 .. 0    0    1    0 .. 1    0    0    0     0828
 1  0  0  1  1  0      0    0    0    0 .. 0    1    0    0 .. 0    0    0    1 .. 1    0    0    0     0418
 1  0  0  1  1  1      0    0    1    0 .. 1    1    0    0 .. 0    0    1    1 .. 1    0    0    0     2c38

 1  0  1  0  0  0      0    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    1     0001
 1  0  1  0  0  1      0    0    0    0 .. 0    0    1    0 .. 0    0    1    0 .. 0    0    0    1     0221
 1  0  1  0  1  0      0    0    0    0 .. 0    0    0    1 .. 0    0    0    1 .. 0    0    0    1     0111
 1  0  1  0  1  1      0    0    1    0 .. 0    0    1    1 .. 0    0    1    1 .. 0    0    0    1     2331

 1  0  1  1  0  0      0    1    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 1    0    0    1     4009
 1  0  1  1  0  1      0    1    0    0 .. 1    0    1    0 .. 0    0    1    0 .. 1    0    0    1     4a29
 1  0  1  1  1  0      0    1    0    0 .. 0    1    0    1 .. 0    0    0    1 .. 1    0    0    1     4519
 1  0  1  1  1  1      0    1    1    0 .. 1    1    1    1 .. 0    0    1    1 .. 1    0    0    1     6f39

 1  1  0  0  0  0      1    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    0    0     8000
 1  1  0  0  0  1      1    0    0    0 .. 0    0    0    0 .. 1    0    1    0 .. 0    0    0    0     80a0
 1  1  0  0  1  0      1    0    0    0 .. 0    0    0    0 .. 0    1    0    1 .. 0    0    0    0     8050
 1  1  0  0  1  1      1    0    1    0 .. 0    0    0    0 .. 1    1    1    1 .. 0    0    0    0     a0f0

 1  1  0  1  0  0      1    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 1    1    0    0     800c
 1  1  0  1  0  1      1    0    0    0 .. 1    0    0    0 .. 1    0    1    0 .. 1    1    0    0     88ac
 1  1  0  1  1  0      1    0    0    0 .. 0    1    0    0 .. 0    1    0    1 .. 1    1    0    0     845c
 1  1  0  1  1  1      1    0    1    0 .. 1    1    0    0 .. 1    1    1    1 .. 1    1    0    0     acfc

 1  1  1  0  0  0      1    0    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 0    0    1    1     8003
 1  1  1  0  0  1      1    0    0    0 .. 0    0    1    0 .. 1    0    1    0 .. 0    0    1    1     82a3
 1  1  1  0  1  0      1    0    0    0 .. 0    0    0    1 .. 0    1    0    1 .. 0    0    1    1     8153
 1  1  1  0  1  1      1    0    1    0 .. 0    0    1    1 .. 1    1    1    1 .. 0    0    1    1     a3f3

 1  1  1  1  0  0      1    1    0    0 .. 0    0    0    0 .. 0    0    0    0 .. 1    1    1    1     c00f
 1  1  1  1  0  1      1    1    0    0 .. 1    0    1    0 .. 1    0    1    0 .. 1    1    1    1     caaf
 1  1  1  1  1  0      1    1    0    0 .. 0    1    0    1 .. 0    1    0    1 .. 1    1    1    1     c55f
 1  1  1  1  1  1      1    1    1    0 .. 1    1    1    1 .. 1    1    1    1 .. 1    1    1    1     efff
P0 P1 M0 M1 BL PF   P0P1 M0M1 BLPF ---- M1PF M1BL M0PF M0BL P1PF P1BL P0PF P0BL M1P0 M1P1 M0P1 M0P0

*/

void Init_TIA(void);
void CatchUpPixels(void);

db TIA_Priority[0x10000];
db TIA_Pixels[160];
dd TIA_Colours[16] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};
dw *TIA_Pixel_PTR;
dd *MyDisplayPointer;

void nTIALineTo(void);
