# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include <err.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

void wait_for_keypressed(void);

SDL_Surface* display_image(SDL_Surface *img);

SDL_Surface* copy_image(SDL_Surface *img);

double *create_matrix(SDL_Surface *img);

char* concat(const char *s1, const char *s2);

# endif
