# ifndef DETECT_H
# define DETECT_H

# include <stdio.h>
# include <err.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

struct matrix
{
    int* p;
    size_t w;
    size_t h;
};

void lines(SDL_Surface* img);
void columns(SDL_Surface *img, int b_line, int e_line);

#endif
