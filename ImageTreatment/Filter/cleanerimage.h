#ifndef _CLEANERIMAGE_H

#define _CLEANERIMAGE_H

# include "../Tools/tools.h"
# include <SDL2/SDL.h>
static float SharpenMatrix[3][3] = {
            { 0.0, -1.0,  0.0},
            {-1.0,  5.0, -1.0},
            { 0.0, -1.0,  0.0}
        };

void grayscale(SDL_Surface *img);

int IsValid(int x, int y, int w, int h);

void ConstrastRenforcement(SDL_Surface* img,int delta);

int Restrict256(int n);

SDL_Surface* Convolute(SDL_Surface* img, float mask[3][3]);

void noiseReduction(SDL_Surface *img);

void blacknwhite(SDL_Surface *img);

void binerize(SDL_Surface *img);

#endif