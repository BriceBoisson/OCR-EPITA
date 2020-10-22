#ifndef _SEGMENTATION_H

#define _SEGMENTATION_H

# include "tools.h"
# include <SDL2/SDL.h>

void CutLines(SDL_Surface *img);

void CutColumn(SDL_Surface * img, int begin_line, int end_line);

int FindBlackPixelInColumn(SDL_Surface *img, int begin_line, int end_line, int start);

void DrawAColumn(SDL_Surface *img,int y, int x, int end_line);

int FindBlackPixel(SDL_Surface *img, int x);

void DrawInImage(SDL_Surface *img);

void DrawALine(SDL_Surface *img,int x);


void lines(SDL_Surface* img);

#endif