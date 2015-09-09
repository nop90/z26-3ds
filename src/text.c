/*
** text.c -- text display
*/

#include "globals.h"
#include "text.h"
#include "video.h"

void clrscr() {
	int i;
	db *sp;
	
	sp = ScreenBuffer;
	for(i=0; i<MaxLines*tiawidth; i++)
		*sp++ = theme;	// *theme*
		
	sp = ScreenBufferPrev;	// force screen to update
	for(i=0; i<MaxLines*tiawidth; i++)
		*sp++ = 0x80;
}

int get_offset() {		// put FPS display at bottom of screen

	switch (height)
	{
	default:   return(0);
	case 240:  return(3);
	case 480:  return(3);
	case 675:  return(-3);
	case 720:  return(3);
	case 768:  return(1);
	case 900:  return(-3);
	case 1024: return(1);
	}
}
*

/*
** our "screen" is 53 characters wide and 28 characters high
*/

void draw_char(char ch, char* font, char* surface, int fontheight, int row, int col, int fg, int bg)
{
	int i,j;
	char *fp;	/* font pointer */
	char *sp;	/* surface pointer */
	char fbyte;	/* font byte */
	
//	row += get_offset();

	fp = font + 8*ch;
	
	// do an extra row at the beginning
	sp = surface + tiawidth*(row) + col;
	for (j=0; j<6; j++) 
	{ 
		*sp++ = bg; 
		if (width == 256) *sp++ = bg;
	}

	for (i=1; i<=fontheight; i++)
	{
		sp = surface + tiawidth*(row+i) + col;
		fbyte = *fp++;		/* pick up a font byte */
		for (j=0; j<6; j++)
		{
			if (fbyte & 0x80)
			{
				*sp++ = fg;
				if (width == 256) *sp++ = fg;
			}
			else
			{	
				*sp++ = bg;
				if (width == 256) *sp++ = bg;
			}
			fbyte <<= 1;
		}
	}
}

void draw_msg_at_color(int x, int y, int fg, int bg) {
	char *mp;	/* message pointer */
	char ch;

	int col = x*6 + 2;	// 2
	int row = y*9 + 2;	// 2

	if (width == 256) col =x*12 + 2;

	if (fg) { fg &= 0xf; fg += theme; }
	if (bg) { bg &= 0xf; bg += theme; }
	
	mp = msg;

	while (1)
	{
		ch = *mp++;
		if (ch == 0) break;
		draw_char(ch, simplex5, (char *) ScreenBuffer, 8, row, col, fg, bg);
		col += 6;
		if (width == 256) col += 6;
	}
}

void draw_long_msg_at_color(int x, int y, int fg, int bg) {
	char *mp;	/* message pointer */
	char ch;

	int col = x*6 + 2;	// 2
	int row = y*9 + 2;	// 2

	if (fg) { fg &= 0xf; fg += theme; }
	if (bg) { bg &= 0xf; bg += theme; }

	mp = msg;

	while (1)
	{
		ch = *mp++;
		if (ch == 0) break;
		if ((ch == '\n') || (col >310))
		{
			row += 10;
			col = 2;	// 2
		}
		if (ch == '\n') continue;
		draw_char(ch, simplex5, (char *) ScreenBuffer, 8, row, col, fg, bg);
		col += 6;
	}
}

/* prints current contents of `msg' at (x,y) */
void draw_msg_at(int x, int y) {
	draw_msg_at_color(x, y, 86, 80);	// was 7,0
}

void grey_msg_at(int x, int y) {
	draw_msg_at_color(x, y, 84, 80);	// was 1,0
}

void grey_hilite_msg_at(int x, int y) {
	draw_msg_at_color(x, y, 0, 80);	// was 0,1
}

void hilite_msg_at(int x, int y) {
	draw_msg_at_color(x, y, 0, 85);	// was 0,7
}

void hilite_char_at(char ch, int x, int y) {
	int col = x*6 + 2;
	int row = y*9 + 2;
	db fg = 0;
	db bg = 87;

	if (fg) { fg &= 0xf; fg += theme; }
	if (bg) { bg &= 0xf; bg += theme; }

	draw_char(ch, simplex5, (char *) ScreenBuffer, 8, row, col - 6, fg, bg);
}


/*
 * the routines above are called from the GUI only ------^
 * 
 * the routines below can be called from random places --v
*/

void show_scanlines()
{
	sprintf(msg,"%4u %5.0f ", LinesInFrame, CurrentFPS);
	if (width == 256) draw_msg_at_color(16, (int) MaxLines/9 - 1, 84, 0);	// was 1,0
	else draw_msg_at_color(42, (int) MaxLines/9 - 1, 84, 0);	// was 1,0

//	sprintf(msg, "%u %4u %5.0f ", SDLticks, LinesInFrame, CurrentFPS);
//	draw_msg_at_color(27, (int) MaxLines/9 - 1, 84, 0);
}

/* called once per frame when there's a status message to display */
void show_transient_status() {
	sprintf(msg, "%s", stat_msg);
	if (width == 256) draw_msg_at_color((26 - strlen(stat_msg))/2, (int) MaxLines/9 - 1, 84, 0);	// was 1,0
	else draw_msg_at_color((52 - strlen(stat_msg))/2, (int) MaxLines/9 - 1, 84, 0);	// was 1,0
}

void clear_status() {
	set_status("");
}

/* call this to set the status message (which will be displayed for
	approximately 1 sec, then cleared) */
void set_status(char *status) {
	strcpy(stat_msg, status);
	status_timer = 60; /* in frames */
}

void srv_print(char *msg)
{
	status_timer = 0;	// don't show the status line when printing a message

	if (srv_screen != NULL)
	{
		clrscr();
		draw_long_msg_at_color(0, 4, 86, 80);
		srv_CopyScreen();
//		SDL_Delay(1000);
		svcSleepThread(1000000000); // 1 sec
	}
}


/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
