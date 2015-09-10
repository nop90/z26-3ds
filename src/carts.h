/*
** recognize cart and set up special properties
*/

#ifndef __CARTS_H__
#define __CARTS_H__

#include "globals.h"

db KoolAide;		/* do KoolAide cheat */
db RSBoxing;		/* do RSBOXING cheat */
dd DefaultCFirst;	/* emu recommends game start here */
db MPdirection;		/* direction mouse must move to emulate paddle */
db MinVol;			/* minimum volume needed to make noise on PC-speaker */
db LG_WrapLine;		/* light gun wrap line */


db Lookup(dd *table);
void RecognizeCart(void);

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

