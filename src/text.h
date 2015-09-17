/*
** text.c -- text display
*/

#ifndef __TEXT_H__
#define __TEXT_H__

#include "globals.h"

void clrscr();
int get_offset();
void draw_char(char ch, char* font, char* surface, int fontheight, int row, int col, int fg, int bg);
void draw_msg_at_color(int x, int y, int fg, int bg);
void draw_long_msg_at_color(int x, int y, int fg, int bg);
void draw_msg_at(int x, int y);
void grey_msg_at(int x, int y);
void grey_hilite_msg_at(int x, int y);
void hilite_msg_at(int x, int y);
void hilite_char_at(char ch, int x, int y);
void show_scanlines();
void show_transient_status();
void clear_status();
void set_status(char *status);
void srv_print(char *msg);

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
