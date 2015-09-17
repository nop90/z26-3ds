/*
	guivideo.h -- video menu
*/

#ifndef __GUIVIDEO_H__
#define __GUIVIDEO_H__

int video_current;	/* currently selected GUI option */
int exit_video;		/* exit video menu */

char startline_data[52];
char screen_data[52];
char line_data[52];
char narrow_data[52];
char Tall_data[52];
char vid_mode_data[52];
char Depth_data[52];
char colourloss_data[52];
char eight_bit_data[52];
char width_data[52];


void set_screen_string();
void set_line_string();
void set_width_string();
void set_height_string();
void set_videomode_string();
void set_Depth_string();
void hand_screen_inc();
void hand_line_inc();
void hand_line_dec();
void hand_narrow_inc();
void hand_narrow_dec() ;
void hand_height_inc();
void hand_height_dec();
void hand_colourloss();
void hand_Depth_inc();
void hand_Depth_dec();
void hand_vid_inc();
void hand_vid_dec();
void hand_video_exit();
void video_gui();

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the
	GNU General Public License Version 2 (GPL).  
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
