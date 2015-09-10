/*
** srv.c -- service code
*/

#include <3ds.h>
#include <sf2d.h>

#include "globals.h"
#include "srv.h"
#include "flip.h"
#include "video.h"
#include "sound.h"
#include "mouse.h"
#include "kidvid.h"


//#include "icon.c"  // needed???
//#include "sdlopengl.c" // todo: move in video what needed



//SDL_Joystick *JoystickTable[16];


void z26_3ds_Init()
{
	Init_SoundQ();

/*
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0 ) /// !!!
	{
		printf("Couldn't initialize 3DS services\n");
		exit(1);
	}
*/
	
//	screen_info = SDL_GetVideoInfo();
	screen_bpp = 32 ; // screen_info->vfmt->BitsPerPixel;
	
//	gl_InitOpenGL();
	screen_width = 400; //screen_surface->w;
	screen_height = 240; // screen_surface->h;

	srv_pitch = 512*4 ; //srv_screen->pitch;
	
	small_screen = sf2d_create_texture(512, 512, TEXFMT_RGBA8, SF2D_PLACE_RAM);   //SDL_CreateRGBSurfaceFrom(&texture_buffer, 512, 512, 32, 4*512, 0, 0, 0, 0);
	large_screen = sf2d_create_texture(1024, 1024, TEXFMT_RGBA8, SF2D_PLACE_RAM); //SDL_CreateRGBSurfaceFrom(&texture_buffer, 1024, 1024, 32, 4*1024, 0, 0, 0, 0);
	tiny_screen =  sf2d_create_texture(256, 256, TEXFMT_RGBA8, SF2D_PLACE_RAM);   //SDL_CreateRGBSurfaceFrom(&texture_buffer, 256, 256, 32, 4*256, 0, 0, 0, 0);
	
	srv_screen = small_screen;

	screen_buffer_count = 0;
	
	ScreenBuffer = RealScreenBuffer1;
	ScreenBufferPrev = RealScreenBuffer2;
        PrevScreenBuffer = RealScreenBuffer3;
        PrevScreenBufferPrev = RealScreenBuffer4;
	
	ClearScreenBuffers();
}

void z26_3ds_quit()
{
  // !!!!! Free textues and quit services
    sf2d_free_texture(small_screen);
    sf2d_free_texture(large_screen);
    sf2d_free_texture(tiny_screen);

}


/*
** event handler
*/

void srv_Events()
{
//	dd sc;
//	SDL_Event event;

//	if (JoystickEnabled) SDL_JoystickUpdate();	/* poll joysticks once per frame */
/*
	while ( SDL_PollEvent(&event) ) {
		switch (event.type) {

			case SDL_KEYDOWN:
				sc = event.key.keysym.sym;
				KeyTable[sc] = 0x80;
				break;

			case SDL_KEYUP:
				sc = event.key.keysym.sym;
				KeyTable[sc] = 0;
				break;

			case SDL_QUIT:
				srv_done = 1;
				break;

			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.which < 17)
					JoystickButton[event.jbutton.which][event.jbutton.button] = 0x80;
				break;
				
			case SDL_JOYBUTTONUP:
				if (event.jbutton.which < 17)
					JoystickButton[event.jbutton.which][event.jbutton.button] = 0;
				break;

			case SDL_JOYAXISMOTION:
				if (event.jaxis.which < 17)
					JoystickAxis[event.jaxis.which][event.jaxis.axis] = event.jaxis.value;
				break;
			default:
				break;
		}
	}
*/

    hidScanInput();
    u32 keys = hidKeysHeld();
	
		KeyTable[KEY_SELECT] = (keys & KEY_SELECT) ? 0x80 : 0;
		KeyTable[KEY_START] = (keys & KEY_START) ? 0x80 : 0;
		KeyTable[KEY_UP] = (keys & KEY_UP) ? 0x80 : 0;
		KeyTable[KEY_DOWN] = (keys & KEY_DOWN) ? 0x80 : 0;
		KeyTable[KEY_LEFT] = (keys & KEY_LEFT) ? 0x80 : 0;
		KeyTable[KEY_RIGHT] = (keys & KEY_RIGHT) ? 0x80 : 0;
		KeyTable[KEY_A] = (keys & KEY_A) ? 0x80 : 0;
		KeyTable[KEY_B] = (keys & KEY_B) ? 0x80 : 0;
		KeyTable[KEY_X] = (keys & KEY_X) ? 0x80 : 0;
		KeyTable[KEY_Y] = (keys & KEY_Y) ? 0x80 : 0;
		KeyTable[KEY_L] = (keys & KEY_L) ? 0x80 : 0;
		KeyTable[KEY_R] = (keys & KEY_R) ? 0x80 : 0;
		
	circlePosition pos;
	hidCircleRead(&pos);
	
	// todo: set joy axis pos for paddle and lightgun

		
}


void Init_Service() {
	srv_SetVideoMode();
	srv_sound_on();
}


void srv_Cleanup() {
	kv_CloseSampleFile();
	srv_sound_off();
}

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
