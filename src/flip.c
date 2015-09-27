/*
** ctrflip.c -- 3DS page flipping code - 3DS port complete
*/

#include <3ds.h>
#include "globals.h"
#include "srv.h"

double srv_get_microseconds()
{
	double ticks;
	
	ctrticks = svcGetSystemTick();
	ticks = ctrticks/TICKS_PER_MSEC;
	return(ticks);
}

void srv_sleep_microseconds(double wait_time)
{
	svcSleepThread((dd) wait_time*1000.0);
}

void srv_reset_timing()
{
	Flips = 0;
	Ticks = 0.0;			/* reset timing calculation */
	FirstFlipTime = 0.0;
	CurrentFPS = 0.0;
	FPStime = 0.0;
	FPSflips = 0;
}

void srv_Flip()
{
	double Now = srv_get_microseconds();
	
	if (Ticks == 0.0)	Ticks = Now;
	if (Flips++ == 0)	FirstFlipTime = Now;
	if (FPStime == 0.0)	FPStime = Now;
	if (PrevFrametime == 0.0)	PrevFrame = Now;

	++FPSflips;
	++FrameSkip_Counter;

	if (Now - FPStime > 1000000.0)	/* update FPS every 4 seconds or ... */
	{	
		CurrentFPS = (FPSflips * 1000000.0)/(Now - FPStime);
		FPStime = Now;
		FPSflips = 0;
	}
	else if (Now - FPStime <= 0.0)	/* ... if there was a time quake */
	{
		CurrentFPS = 0.0;
		FPStime = Now;
		FPSflips = 0;
	}
	
	if(FPSLimit && (Now - PrevFrametime < Ticks_per_Frame/1000)) svcSleepThread(Ticks_per_Frame/1000 - Now + PrevFrametime);
	PrevFrametime = Now;
	if(FrameSkip_Counter>FrameSkip_Value) FrameSkip_Counter = 0;

}

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/
