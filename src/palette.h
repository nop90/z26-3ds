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

db NTSC_RGB_table[] = 
{
 120, 120, 120,		/* (00) <120,120,120> grey */
 128, 144,   0,		/* (10) <128,144,2>   gold */
 163, 117,  19,		/* (20) <163,117,19>  yellow orange */
 183,  97,  64,		/* (30) <183,97,64>   yar's bright orange */
 185,  78, 104,		/* (40) <185,83,124>  pink */
 175,  68, 173,		/* (50) <175,78,173>  purple */
 153,  71, 206,		/* (60) <153,81,211>  blue purple */
 124,  81, 213,		/* (70) <124,91,228>  atlantis right blinker blue */
 97,   97, 207,		/* (80) <97,107,217>  blue */
 75,  112, 188,		/* (90) <75,122,188>  light blue */
 64,  126, 150,		/* (a0) <64,136,145>  atlantis turquoise */
 64,  139, 108,		/* (b0) <64,144,103>  green blue */
 75,  145,  70,		/* (c0) <75,145,65>   light green */
 91,  141,  45,		/* (d0) <91,141,45>   yellow green */
 112, 130,  40,		/* (e0) <112,130,40>  orange green */
 130, 122,  45		/* (f0) <130,122,45>  light orange */
};

db set_luma(int luma, int val);

void NTSC_Palette();

/*
** PAL stuff
*/

/* note: RGB values are for the $x6 color */
/* PAL colors from Oliver Achten screen capture */

db PAL_RGB_table[] = 
{
 116, 116, 116,		/* (00) <116,116,116> grey */
 116, 116, 116,		/* (10) <116,116,116> grey */
 143, 118, 23,          /* (20) <143,118,23>  gold */
 87,  148, 21,		/* (30) <87,148,21>   yellow green */
 166, 101, 58,		/* (40) <166,101,58>  orange brown */
 67,  151, 57,		/* (50) <67,151,57>   light green */
 176, 87,  107,         /* (60) <176,87,107>  pink */
 56,  147, 106,         /* (70) <56,147,106>  blue green */
 169, 82,  155,         /* (80) <169,82,155>  purple */
 61,  136, 154,		/* (90) <61,136,154>  turquoise */
 155, 81,  196,		/* (a0) <155,81,196>  lilac */
 78,  119, 195,		/* (b0) <78,119,195>  light blue */
 129, 90,  217,         /* (c0) <129,90,217>  purple blue */
 102, 103, 218,		/* (d0) <102,103,218> blue */
 116, 116, 116,		/* (e0) <116,116,116> grey */
 116, 116, 116		/* (f0) <116,116,116> grey */
};


void PAL_Palette();

db SECAM_RGB_table[] = 
{
   0,   0,   0,		/* black */
  33,  33, 255,		/* blue */
 240,  60, 121,		/* red */
 255,  60, 255,		/* magenta */
 127, 255,   0,		/* green */
 127, 255, 255,		/* cyan */
 255, 255,  63,		/* yellow */
 255, 255, 255		/* white */
};

void SECAM_Palette();

void GeneratePalette();

#endif

