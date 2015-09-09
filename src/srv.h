/*
** srv.c -- service code
*/
#pragma once

#include <3ds.h>
#include <sf2d.h>
#include "globals.h"

sf2d_texture *srv_screen = NULL;
sf2d_texture *small_screen = NULL;
sf2d_texture *large_screen = NULL;
sf2d_texture *tiny_screen = NULL;

db *srv_buffer;
dd srv_pitch;

dd Vert, Horiz;		/* offsets into window or video display where 2600 pixels are rendered in pixels*/
dd width, height;	/* dimensions of current window or video display in pixels */

db *screen_pixels;      /* pointer to display screen */
db *emu_pixels;         /* pointer to current emulator buffer */
db *emu_pixels_prev;    /* pointer to previous emulator buffer */
db *prev_emu_pixels;	/* previous pointer to display screen */
db *prev_emu_pixels_prev; /* previous pointer to previous emulator buffer */

db screen_buffer_count = 0;
db srv_done = 0;
dd odd = 0;		/* is the frame number odd? -- for interlaced modes */

dd srv_colortab_hi[128];		/* for mapping atari 8-bit colors to 32-bit colors */
dd srv_colortab_med[128];		/* for soft scanlines */
dd srv_colortab_low[128];


void z26_3ds_Init();
void z26_3ds_quit();
void srv_Events();
void Init_Service();
void srv_Cleanup();

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
