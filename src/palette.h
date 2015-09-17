/*
** palette.c -- palette setup code
*/

/*
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

#ifndef __PALETTE_H__
#define __PALETTE_H__


#include "globals.h"

/*
** NTSC stuff
*/

/* note: RGB values are for the $x6 color */

db NTSC_RGB_table[48];

db set_luma(int luma, int val);

void NTSC_Palette();

/*
** PAL stuff
*/

/* note: RGB values are for the $x6 color */
/* PAL colors from Oliver Achten screen capture */

db PAL_RGB_table[48];


void PAL_Palette();

/*
** SECAM stuff
*/

db SECAM_RGB_table[24];

void SECAM_Palette();

void GeneratePalette();

#endif

