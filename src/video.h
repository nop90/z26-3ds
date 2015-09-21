/*
	video.h
*/

#ifndef __VIDEO_H__
#define __VIDEO_H__


#include "globals.h"

//dd texture_buffer[1024*1024];

/*
typedef struct{
  db r;
  db g;
  db b;
  db unused;
} RGB32_Color;
*/

void ClearScreenBuffers();
void CreateScreen();
void DrawScreen();
void srv_SetPalette();
// void srv_InitJoystick();
void srv_SetVideoMode();
void srv_CopyScreen();
void gui_CopyScreen();

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
