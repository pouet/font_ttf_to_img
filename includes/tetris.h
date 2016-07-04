#ifndef INCLUDES_H
#define INCLUDES_H

#include "SDL.h"
 
/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

#define SURFACE_TRANSPARENT_COLOR 0x00FFFFFF

enum {
	SDL_FLAGS = SDL_INIT_VIDEO
};

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

struct gVars_s {
	SDL_Window		*pWin;
	SDL_Renderer	*pRen;
};

/* ********************************* */
/* *           Globales            * */
/* ********************************* */
 
extern struct gVars_s gVars;

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */


#endif
