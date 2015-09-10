/*
** gui.c -- graphical user interface
*/

/* 20040530 bkw */

#ifndef __GUI_H__
#define __GUI_H__

#include "guiutil.h"

#define GUI_WIDTH 38
#define FONT_WIDTH 6
#define FONT_HEIGHT 9

/*** global variables */

int exit_gui = 0;	/* handlers set this to 1 to exit the GUI */
int gui_current = 0;	/* currently selected GUI option */

gui_entry *current_gui_items = NULL;
db OldPaletteNumber;	/* remember game palette number */
char newfile[260];

void gui_SetVideoMode();

void run_rom();

void hand_load_rom();

void hand_exit() ;

void gui();

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
