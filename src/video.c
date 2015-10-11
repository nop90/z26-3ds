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
//#include "pixcopy.h"

void ClearScreenBuffers()
{

	int i;
	u16 * fb;
	fb= (u16*) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	for (i=0; i<400*240;i++) fb[i] = 0;
	fb= (u16*) gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	for (i=0; i<320*240;i++) fb[i] = 0;
    gfxFlushBuffers();
    gfxSwapBuffers();
	fb= (u16*) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	for (i=0; i<400*240;i++) fb[i] = 0;
	fb= (u16*) gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	for (i=0; i<320*240;i++) fb[i] = 0;
/*
	gpuClearBuffers(0x00000000);
    gfxSwapBuffers();
*/
}


void CreateScreen()	// need to be able to force video mode change
{

}


void DrawScreen() {

	dd x;
	db	*topscreen = (db*) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL) +15;
	
    if(GamePaused || (!FrameSkip_Counter)) { //draws game frame only when FrameSkip_Counter == 0 
//		if (!DrawHack_Skipcols && !GamePaused)
		if (!GamePaused)
			for(x=480*40; x<480*360; x+=960)
				memcpy(topscreen+x+480, topscreen+x, 450); // 480);
		gfxFlushBuffers();
		gfxSwapBuffers();
//		gpuClearBuffers(0x00000000);

	}
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
//	RGB32_Color palette[256];

	GeneratePalette();
	for ( i=0; i<128; i++)
	{
		red = PCXPalette[3*i]>>3;
		grn = PCXPalette[3*i+1]>>3;
		blu = PCXPalette[3*i+2]>>3;
/*
		palette[i].r = red;
		palette[i].g = grn;
		palette[i].b = blu;
*/
/*
		srv_colortab_hi[i] =  0xf | (red<<11) |  (grn<<6) | (blu<<1) ;
		srv_colortab_med[i] = 0xf | (((red*med)/100)<<11) |  (((grn*med)/100)<<6) | (((red*med)/100)<<1) ; 
		srv_colortab_low[i] = 0xf | (((red*hi)/100)<<11) |  (((grn*hi)/100)<<6) | (((red*hi)/100)<<1) ; 
*/
		srv_colortab_hi[i] =  0x1 | (red<<11) |  (grn<<6) | (blu<<1) ;
		srv_colortab_med[i] = 0x1 | (((red*med)/100)<<11) |  (((grn*med)/100)<<6) | (((red*med)/100)<<1) ; 
		srv_colortab_low[i] = 0x1 | (((red*hi)/100)<<11) |  (((grn*hi)/100)<<6) | (((red*hi)/100)<<1) ; 
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
	
	Vert = 0;//(height - scanlinespread*MaxLines) / 2;
	Horiz = 0;//(width - pixelspread*tiawidth) / 2;
	srv_pitch = 512*4; // srv_screen->pitch;
	if (status_timer > 0) 
		{
			show_transient_status();
			status_timer--;
		}
//	else if (ShowLineCount && !GamePaused)
	else if (!GamePaused)
		{
			show_scanlines();
		}
	
	lines2draw = scanlinespread;
	DrawScreen();   
	
	srv_Flip();
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

	srv_pitch = 512*4; // srv_screen->pitch;
	lines2draw = scanlinespread;
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
