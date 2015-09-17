/*
** guitweaks.c --  menu
* 
* lightgun wrapping ?
*/

#ifndef __GUITWEAKS_H__
#define __GUITWEAKS_H__

#include "globals.h"

int tweaks_current;	/* currently selected GUI option */
int exit_tweaks;	/* exit timing menu */

char mpx_data[52];
char mpy_data[52];
char paddle_sensitivity_data[52];
char paddle_adjust_data[52];
char lightgun_cycles_data[52];
char lightgun_scanlines_data[52];

void set_mpx_string();
void hand_mpx_inc();
void hand_mpx_dec();
void set_mpy_string() ;
void hand_mpy_inc();
void hand_mpy_dec();
void set_paddle_sensitivity_string();
void hand_paddle_sensitivity_inc();
void hand_paddle_sensitivity_dec();
void set_paddle_adjust_string();
void hand_paddle_adjust_inc();
void hand_paddle_adjust_dec();
void set_lightgun_cycles_string();
void hand_lightgun_cycles_inc();
void hand_lightgun_cycles_dec();
void set_lightgun_scanlines_string();
void hand_lightgun_scanlines_inc();
void hand_lightgun_scanlines_dec();
void hand_tweaks_exit();

/* Main entry point. Called by gui() */

void tweaks_gui();

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
