/*
** guifilelist.h 
*/

#pagma once
#include "globals.h"

void directory_failed();
void get_list(int file_type);
void get_file_list();
int draw_file_list(int cur, int window_line, int ymax);
// int find_next_rom(int curfile, SDLKey k);
int file_selector(char *result);

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
