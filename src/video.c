/*
	video.c -- video code
*/

// const SDL_VideoInfo *screen_info;

// SDL_Surface *screen_surface;  // !!

#include <string.h>
#include "globals.h"
#include "flip.h"
#include "video.h"
#include "srv.h"
#include "palette.h"
#include "position.h"
#include "text.h"
#include "pixcopy.h"

void ClearScreenBuffers()
{
	memset(RealScreenBuffer1, 0,    MaxLines*tiawidth);
	memset(RealScreenBuffer2, 0, MaxLines*tiawidth); // memset(RealScreenBuffer2, 0x80, MaxLines*tiawidth);
	memset(RealScreenBuffer3, 0,    MaxLines*tiawidth);
	memset(RealScreenBuffer4, 0, MaxLines*tiawidth); // memset(RealScreenBuffer4, 0x80, MaxLines*tiawidth);

	memset(texture_buffer, 0, 4*1024*1024);
}


void CreateScreen()	// need to be able to force video mode change
{
//	gl_CreateScreen();
/*
int	vsize = (screen_height/MaxLines)*MaxLines;
int	vpos, hoffset, maxheight;
int	maxstretch = (screen_width * 3) / 40;

	if (vsize+Tall*4 > screen_height)	maxheight = screen_height;
	else					maxheight = vsize+Tall*4;
		
	if (Narrow > maxstretch)		hoffset = maxstretch*4;
	else					hoffset = Narrow*4;

	vpos = (screen_height - maxheight)/2;

//	SDL_WM_SetCaption(FileName, FileName);
	
//	if (MouseRude|FullScreen)
//		SDL_ShowCursor(SDL_DISABLE);
//	else	
//		SDL_ShowCursor(SDL_ENABLE);
*/
}



void DrawScreen() {

	sf2d_texture_tile32(srv_screen);
	sf2d_texture_tile32(srv_gui);


    sf2d_start_frame(GFX_TOP, GFX_LEFT);
	
	if (FullScreen)
		sf2d_draw_texture_part_scale(srv_screen, 0, 0, 0, 0, 160, 240, 2.5, 1); //1.24);
	else
		sf2d_draw_texture_part_scale(srv_screen, 40, 0, 0, 0, 160, 240, 2, 1);
	sf2d_end_frame();

    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

	sf2d_draw_texture(srv_gui, 0, 0);

	sf2d_end_frame();
    gfxFlushBuffers();

    gfxFlushBuffers();

    sf2d_swapbuffers();


}

/*
** set up the palette
*/

void srv_SetPalette()
{
	
	
	int i;
		
	dd hi = Depth;
	dd med = (Depth + 100)/2;

	db red, grn, blu;
	RGB32_Color palette[256];

	GeneratePalette();
	for ( i=0; i<128; i++)
	{
		red = PCXPalette[3*i];
		grn = PCXPalette[3*i+1];
		blu = PCXPalette[3*i+2];
/*
		palette[i].r = red;
		palette[i].g = grn;
		palette[i].b = blu;
*/
		srv_colortab_hi[i] =  0xff000000 | (blu<<16) |  (grn<<8) |red ; // SDL_MapRGB(srv_screen->format, red, grn, blu);
		srv_colortab_med[i] = 0xff000000 | (((blu*med)/100)<<16) |  (((grn*med)/100)<<8) | ((red*med)/100) ; // SDL_MapRGB(srv_screen->format, (red*med)/100, (grn*med)/100, (blu*med)/100);
		srv_colortab_low[i] = 0xff000000 | (((blu*hi)/100)<<16) |  (((grn*hi)/100)<<8) | ((red*hi)/100) ; // SDL_MapRGB(srv_screen->format, (red*hi)/100,  (grn*hi)/100,  (blu*hi)/100);
	}
}


/*
void srv_InitJoystick() {
dd i;

	if (JoystickEnabled)	// joystick support not disabled with -iJ 
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		if ((SDL_NumJoysticks()>0)&&(SDL_NumJoysticks()<17))
		{
			for (i=0; i<SDL_NumJoysticks(); i++)
			{
				JoystickTable[i]=SDL_JoystickOpen(i);
				// Stelladaptor only has 2 buttons and 2 axes 
				if ((SDL_JoystickNumAxes(JoystickTable[i]) == 2) &&
				    (SDL_JoystickNumButtons(JoystickTable[i]) == 2) &&
				    (SDL_JoystickNumHats(JoystickTable[i]) == 0) &&
				    (SDL_JoystickNumBalls(JoystickTable[i]) == 0) &&
				    (StelladaptorEnabled))
				{
					Stelladaptor[i] = 1;
				}
				else Stelladaptor[i] = 0;
			}
//			SDL_JoystickEventState(SDL_ENABLE);
		}
		else JoystickEnabled = 0;	// disable joystick polling 
	}

}
*/

void srv_SetVideoMode() {

	/* If user gave a valid video mode, use it, or else use default */
//	if (VideoMode > 5) VideoMode = 0; 
	VideoMode = 0; 
	
//	srv_CreateIcon(); // !!!! mantenere???
//	SDL_WM_SetIcon(z26Icon, z26IconMask); // !!!! mantenere???
//	srv_InitJoystick();


	MaxLines = 240; width = 320;  height = 240;
/*
	switch(VideoMode)
	{
	default:
	case 0:	 MaxLines = 256; width = 512;  height = 512;  break;
	case 1:	 MaxLines = 256; width = 512;  height = 512;  break;
	case 2:	 MaxLines = 256; width = 1024; height = 1024; srv_screen = large_screen; break;
	case 3:	 MaxLines = 256; width = 1024; height = 1024; srv_screen = large_screen; break;
	case 4:	 MaxLines = 256; width = 256;  height = 256;  srv_screen = tiny_screen;  break;
	case 5:	 MaxLines = 256; width = 256;  height = 256;  srv_screen = tiny_screen;  break;
	}
*/

	scanlinespread = height / MaxLines;

	pixelspread = width / 512;
	if (pixelspread == 0) pixelspread = 1;

	ClearScreenBuffers();
	CreateScreen();
	srv_SetPalette();

//	if(GrabInput) SDL_WM_GrabInput(SDL_GRAB_ON);
	
	position_game(); 	/* set game's vertical position */
}


void srv_CopyScreen()
{
	void (*copy)();
	dd bpp = 4; // srv_screen->format->BytesPerPixel;
	dd i;
	dd oldpixelspread = pixelspread;
	
	odd++;		  // alternate startline for interlaced display
	
//	if (tiawidth == 160) pixelspread *= 2;	// for the narrow tia engine
	
	Vert = 0;//(height - scanlinespread*MaxLines) / 2;
	Horiz = 0;//(width - pixelspread*tiawidth) / 2;
//	if (width == 256) Horiz = (width - pixelspread*tiawidth/2) / 2;

	srv_buffer = srv_screen->data; //srv_screen->pixels;
	srv_pitch = 512*4; // srv_screen->pitch;

	emu_pixels = ScreenBuffer;
	emu_pixels_prev = ScreenBufferPrev;
	prev_emu_pixels = PrevScreenBuffer;
	prev_emu_pixels_prev = PrevScreenBufferPrev;

	screen_pixels = srv_buffer + Horiz*bpp + (Vert)*srv_pitch;
	
	if (status_timer > 0) 
		{
			show_transient_status();
			status_timer--;
		}
		else if (ShowLineCount && !GamePaused)
		{
			show_scanlines();
		}
	
	lines2draw = scanlinespread;

	copy = FastPixCopy32;
//	copy = PixCopy32_2;
/*
	if (scanlinespread == 1) 
		copy = FastPixCopy32;
	else if (DoInterlace)
	{
		lines2draw = scanlinespread / 2;
		if (odd & 1) screen_pixels += lines2draw * srv_pitch;
	}
	else if (scanlinespread == 2)
		copy = PixCopy32_2;
	else if (scanlinespread == 4)
		copy = PixCopy32_4;
*/
	for (i=0; i<MaxLines; ++i)
	{	
		(*copy)();
		screen_pixels += scanlinespread * srv_pitch;
		emu_pixels += tiawidth;
		emu_pixels_prev += tiawidth;
		prev_emu_pixels += tiawidth;
		prev_emu_pixels_prev += tiawidth;
	}

	srv_screen->tiled = 0;
	DrawScreen();   
	
	srv_Flip();
//	memset(ScreenBuffer, 0, MaxLines*tiawidth);
//	memset(srv_buffer, 0, 512*256*4);

	
	pixelspread = oldpixelspread;
}



void gui_CopyScreen()
{
	db oldDoInterlace = DoInterlace;
	dd oldtiawidth = tiawidth;
	
	DoInterlace = 0;
	tiawidth = 320;
	
 	void (*copy)();
	dd bpp = 4; // srv_screen->format->BytesPerPixel;
	dd i;
	dd oldpixelspread = pixelspread;
	
	odd++;		  // alternate startline for interlaced display
	
	Vert = 0;//(height - scanlinespread*MaxLines) / 2;
	Horiz = 0;//(width - pixelspread*tiawidth) / 2;

	srv_buffer = srv_gui->data; //srv_screen->pixels;
	srv_pitch = 512*4; // srv_screen->pitch;

	emu_pixels = ScreenBuffer;
	emu_pixels_prev = ScreenBufferPrev;
	prev_emu_pixels = PrevScreenBuffer;
	prev_emu_pixels_prev = PrevScreenBufferPrev;

	screen_pixels = srv_buffer ;//+ Horiz*bpp + (Vert)*srv_pitch;
	
	if (status_timer > 0) 
		{
			show_transient_status();
			status_timer--;
		}
		else if (ShowLineCount && !GamePaused)
		{
			show_scanlines();
		}
	
	lines2draw = scanlinespread;

	copy = PixCopy32_2;
/*
	if (scanlinespread == 1) 
		copy = FastPixCopy32;
	else if (DoInterlace)
	{
		lines2draw = scanlinespread / 2;
		if (odd & 1) screen_pixels += lines2draw * srv_pitch;
	}
	else if (scanlinespread == 2)
		copy = PixCopy32_2;
	else if (scanlinespread == 4)
		copy = PixCopy32_4;
*/
	for (i=0; i<MaxLines; ++i)
	{	
		(*copy)();
		screen_pixels += scanlinespread * srv_pitch;
		emu_pixels += tiawidth;
		emu_pixels_prev += tiawidth;
		prev_emu_pixels += tiawidth;
		prev_emu_pixels_prev += tiawidth;
	}

	srv_gui->tiled = 0;
	DrawScreen();   
	
	srv_Flip();
	
	pixelspread = oldpixelspread;
	
	DoInterlace = oldDoInterlace;
	tiawidth = oldtiawidth;
}



/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
