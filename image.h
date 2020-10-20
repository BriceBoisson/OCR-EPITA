#ifndef IMG_H
#define IMG_H

# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

SDL_Surface* load_image(char* path);

SDL_Window* display_img(SDL_Surface* image);

void wait_for_keypressed();

void SDL_FreeSurface(SDL_Surface *surface);

#endif
