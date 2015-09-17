/*
	pixcopy.c -- pixel copy routines
*/


#ifndef __PIXCOPY_H__
#define __PIXCOPY_H__

#include "globals.h"

// general purpose routine for interlacing

void PixCopy32();
void FastPixCopy32();
void PixCopy32_2();
void PixCopy32_4();

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
