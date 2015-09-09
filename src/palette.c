/*
** palette.c -- palette setup code
*/

/*
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/


#include "globals.h"
#include "palette.h"
/*
** NTSC stuff
*/

db set_luma(int luma, int val)
{
	val += luma*20 - 60;
	if (val<0) return 0;
	if (val>255) return 255;
	return(val);
}

void NTSC_Palette()
{
	int chroma, luma, i;

	for (chroma = 0; chroma <=15; chroma++)
		for (luma=0; luma<=7; luma++)
			for (i=0; i<3; i++)
				PCXPalette[chroma*3*8 + luma*3+i] = set_luma(luma, NTSC_RGB_table[chroma*3+i]);
	PCXPalette[0] = 0; PCXPalette[1] = 0; PCXPalette[2] = 0;
}

/*
** PAL stuff
*/

void PAL_Palette()
{
	int chroma, luma, i;

	for (chroma = 0; chroma <=15; chroma++)
		for (luma=0; luma<=7; luma++)
			for (i=0; i<3; i++)
				PCXPalette[chroma*3*8 + luma*3+i] = set_luma(luma, PAL_RGB_table[chroma*3+i]);

	for(i=0; i<=2; i++)
	{	
		PCXPalette[0+i]=0;;
		PCXPalette[3*8+i]=0;;
		PCXPalette[14*3*8+i]=0;
		PCXPalette[15*3*8+i]=0;
	}
}

/*
** SECAM stuff
*/

void SECAM_Palette()
{
	int i,j;
	unsigned char *d, *s;

	d = PCXPalette;			/* dest pointer */
	
	for (i=0; i<16; i++)
	{
		s = SECAM_RGB_table;	/* source pointer */
		for(j=1; j<=24; j++)
			*d++ = *s++;
	}
}


/*
** generate appropriate palette
*/

void GeneratePalette()
{
//	printf("palette number %d\n", PaletteNumber);
	
	switch(PaletteNumber)
	{
	case 0:  NTSC_Palette();  break;
	case 1:  PAL_Palette();   break;
	case 2:  SECAM_Palette(); break;
	default: NTSC_Palette();  break;
	}
}


