# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <err.h>

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void array_select_sort(int array[], size_t len);

void array_swap(int array[], size_t i, size_t j);

SDL_Surface* CreateWhiteSurface(int x, int y, SDL_Surface *img);

SDL_Surface* resizechar(SDL_Surface* img);

int FindBlackPixelv2(SDL_Surface *img, int x);

SDL_Surface* copy_image(SDL_Surface *img);

SDL_Surface* resize(SDL_Surface *img, int x,int y);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);





# endif
