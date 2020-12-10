# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <err.h>

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void array_swap(int array[], size_t i, size_t j);

double* resizechar(SDL_Surface* img, int size);

int FindBlackPixelrow(double *img, int w, int x);

int FindBlackPixelcol(double *img, int w, int h, int x);

double* resize(double *img, int w, int h, int x, int y);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void get_binerize_matrix(SDL_Surface *img, double *image);


# endif
