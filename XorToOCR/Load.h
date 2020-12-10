# ifndef LOAD_H
# define LOAD_H

# include <stdlib.h>

#include "../ImageTreatment/Tools/tools.h"
# include <stdio.h>
# include <SDL2/SDL.h>
# include <err.h>


void array_swap(int array[], size_t i, size_t j);

double* resizechar(SDL_Surface* img, int size);

int FindBlackPixelrow(double *img, int w, int x);

int FindBlackPixelcol(double *img, int w, int h, int x);

double* resizearray(double *img, int w, int h, int x, int y);

void get_binerize_matrix(SDL_Surface *img, double *image);


# endif
