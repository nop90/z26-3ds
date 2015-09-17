/*
** guifilelist.h 
*/

#ifndef __GUIFILELIST_H__
#define __GUIFILELIST_H__

#include "globals.h"

dd match;
//SDLKey matched[100];
dw matched[100];

#define MAX_ENTS 20000
#define MAX_LEN 256
#define FT_DIRS 0
#define FT_FILES 1

static int filesread;
static char *file_list[MAX_ENTS+1];
static char file_names[(MAX_ENTS+1)*(MAX_LEN+1)];

int window_line;
int curfile;
int first_filelist;

void directory_failed();
void get_list(int file_type);
void get_file_list();
int draw_file_list(int cur, int window_line, int ymax);
// int find_next_rom(int curfile, SDLKey k);
int file_selector(char *result);

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
