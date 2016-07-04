#ifndef INCLUDES_H
#define INCLUDES_H

#include "SDL.h"
 
/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

#define OUTPUT_NAME "font.bmp"

enum {
	SDL_FLAGS = SDL_INIT_VIDEO,
	SIZE_TAB = '~' - ' ' + 1
};

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

struct gVars_s {
	TTF_Font *pFont;
	int nSize;
};

/* ********************************* */
/* *           Globales            * */
/* ********************************* */
 
extern struct gVars_s gVars;

#endif
