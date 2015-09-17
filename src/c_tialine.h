/*

	tialine.c -- generate a raster line


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#ifndef __C_TIALINE_H__
#define __C_TIALINE_H__

#include "globals.h"

/* just to be able to compile with trace */
dd P0_Position;
dd P1_Position;
dd M0_Position;
dd M1_Position;
dd BL_Position;


dd TIACollide;	// state of the 15 collision bits

dd TIA_Last_Pixel;	// remember how far we have rendered this line
db TIA_Display_HBlank;	// show HMOVE bar in this line
dd TIA_HMOVE_Setup;	// it takes several steps to setup an HMOVE
dd TIA_HMOVE_Clock;	// how many HMOVE clocks since last HMOVE command
db TIA_HMOVE_Latches;	// are we done with HMOVE pulses
db TIA_HMOVE_DoMove;	// do we need to apply more HMOVE pulses
// how far to move object with HMOVE (0-15)
db TIA_HMP0_Value;
db TIA_HMP1_Value;
db TIA_HMM0_Value;
db TIA_HMM1_Value;
db TIA_HMBL_Value;
db TIA_Pixel_State;	// which objects to draw in this pixel (one bit each)
db TIA_Mask_Objects;	// enable VBLANK and let user disable objects
db TIA_Do_Output;	// if line is offscreen, don't copy pixels to buffer
db CTRLPF_PF_Reflect;	// reflect PF in right half of screen
db Current_PF_Pixel;	// state of currently displayed PF pixel
// how wide are we supposed to display this pixel
db NUSIZ_P0_width;
db NUSIZ_P1_width;
db NUSIZ_M0_width;
db NUSIZ_M1_width;
db CTRLPF_BL_width;
// reset missile to pixel 4 of player main copy
db TIA_RESMP0;
db TIA_RESMP1;
// use 'old' object data
db TIA_VDELP0;
db TIA_VDELP1;
db TIA_VDELBL;
// reflect player
dd TIA_REFP0;
dd TIA_REFP1;
// graphics data for objects
dd TIA_GRP0_new;
dd TIA_GRP0_old;
dd TIA_GRP1_new;
dd TIA_GRP1_old;
dd TIA_ENAM0;
dd TIA_ENAM1;
dd TIA_ENABL_new;
dd TIA_ENABL_old;
// which object copies do we show
db NUSIZ0_number;
db NUSIZ1_number;
db CTRLPF_Score;	// use score mode colours for playfield
db CTRLPF_Priority;	// has playfield priority over movable objects
// object pixel counters for visible part of screen
dd TIA_P0_counter;
dd TIA_P1_counter;
dd TIA_M0_counter;
dd TIA_M1_counter;
dd TIA_BL_counter;
// VBLANK, GRP0, GRP1, ENAM0, ENAM1, ENABL, REFP0, REFP1, PF0, PF1, PF2
// need one extra pixel for the write to take effect
// -> render one pixel ahead of counter before updating register state
db TIA_Delayed_Write;

#define BG_COLOUR 0
#define PF_COLOUR 1
#define P1_COLOUR 2
#define P0_COLOUR 3

dw TIA_Colour_Table[4];

db TIA_Priority_Table[2][64];
db TIA_Score_Priority_Table[2][64];

db ObjectStartTable[8][320];


dd TIA_P0_counter_reset;
dd TIA_P1_counter_reset;
dd TIA_M0_counter_reset;
dd TIA_M1_counter_reset;
dd TIA_BL_counter_reset;

dd TIA_Playfield_Value;
dd TIA_REFPF_Flag;
db TIA_VBLANK;

dw LoopCount;	// counter for the CatchUpPixels loop
dw CountLoop;

dd Pointer_Index_P0;
dd Pointer_Index_P1;
dd Pointer_Index_M0;
dd Pointer_Index_M1;
dd Pointer_Index_BL;

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

dd TIA_Playfield_Pixels[80];
dd TIA_Playfield_Bits;	// all 3 PF register values (0x00 PF0 PF1 PF2)

// where to draw missiles; used for generating the TIA_Mx_Tables
db Object_Table[8][4];

dw TIA_Collision_Table[64];

db TIA_Priority[0x10000];
db TIA_Pixels[160];
dd TIA_Colours[16];
dw *TIA_Pixel_PTR;
dd *MyDisplayPointer;

void Init_TIA(void);
void CatchUpPixels(void);void nTIALineTo(void);

#endif
