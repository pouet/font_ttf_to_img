#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "includes.h"

struct gVars_s gVars;
char const *gProgName;

void	usage(void) {
	fprintf(stderr, "usage : %s font.ttf [size]\n", gProgName);
}

int		initVideo(void) {
	if (TTF_Init() < 0) {
		fprintf(stderr, "TTF_Init : %s\n", TTF_GetError());
		return -1;
	}
	atexit(TTF_Quit);
	return 0;
}

int		init(char *pFont, char *pSize) {
	int nSize = 0;
	char *pEnd;

	if (initVideo() < 0)
		return -1;
	if (pSize != NULL) {
		nSize = strtol(pSize, &pEnd, 10);
		if (nSize < 0 || nSize > 256 || *pEnd != '\0') {
			fprintf(stderr, "%s: invalid size font\n", gProgName);
			usage();
		}
	}
	gVars.nSize = nSize;
	gVars.pFont = TTF_OpenFont(pFont, nSize);
	if (gVars.pFont == NULL) {
		fprintf(stderr, "SDL_ttf: %s\n", TTF_GetError());
		return -1;
	}
	return 0;
}

int		writeSurface(void) {
	char pString[SIZE_TAB + 1] = "";
	SDL_Color color = { 0, 0, 0, 0 };
	SDL_Surface *pSfc;
	SDL_Surface *pTmp;
	SDL_Rect r;
	int i;

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	for (i = 0; i < SIZE_TAB; i++)
		pString[i] = i + ' ';
	pString[i] = '\0';
	TTF_SizeText(gVars.pFont, pString, NULL, &r.h);
	r.x = 0;
	r.y = 0;
	r.w = r.h;
	printf("Font will be H: %d W: %d\n", r.h, r.w * SIZE_TAB);

	pSfc = SDL_CreateRGBSurface(0, r.w * (SIZE_TAB + 1), r.h, 32,
			rmask, gmask, bmask, amask);
	SDL_FillRect(pSfc, NULL, ~0);

	pString[1] = '\0';
	for (i = 0; i < SIZE_TAB; i++) {
		pString[0] = i + ' ';
		pTmp = TTF_RenderText_Solid(gVars.pFont, pString, color);
		SDL_BlitSurface(pTmp, NULL, pSfc, &r);
		SDL_FreeSurface(pTmp);
		r.x += r.w;
	}

	if (SDL_SaveBMP(pSfc, OUTPUT_NAME) < 0) {
		fprintf(stderr, "SDL: %s\n", SDL_GetError());
		return -1;
	}
	printf("File %s was created !\n", OUTPUT_NAME);
	SDL_FreeSurface(pSfc);
	return 0;
}

int		main(int ac, char **av) {
	gProgName = av[0];

	if (ac < 2 || ac > 3) {
		usage();
		return EXIT_FAILURE;
	}
	if (init(av[1], av[2]) < 0)
		return EXIT_FAILURE;
	if (writeSurface() < 0)
		return EXIT_FAILURE;

	return 0;
}
