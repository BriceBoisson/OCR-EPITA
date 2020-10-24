# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include <err.h>
# include "tools.h"

SDL_Surface* lineCut(SDL_Surface *img);

void isolateLine(SDL_Surface *img, struct Neural_Network *net);

void cuttedSurface(SDL_Surface *img, int firstCut,
                    int lastCut, struct Neural_Network *net);

void charCut(SDL_Surface *img);

SDL_Surface* increaseChar(SDL_Surface *img);

void isolateChar(SDL_Surface *img, struct Neural_Network *net);

# endif
