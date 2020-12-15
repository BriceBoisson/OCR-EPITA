#ifndef _SEGMENTATION_H

#define _SEGMENTATION_H

# include "../Tools/tools.h"
# include <SDL2/SDL.h>

void CutLines(SDL_Surface *img, int d);

void cutword(SDL_Surface *img);

int seuil(SDL_Surface *img);

void drawBlocksLines (SDL_Surface *img, SDL_Surface *imgRLSA);

void histo(SDL_Surface *img, int* histo1);

int average1(SDL_Surface *img);

void drawBlocksMulti(SDL_Surface *img, SDL_Surface *imgHor, SDL_Surface *imgVer);

void drawBlocks(SDL_Surface *img, SDL_Surface *imgHor);

void cutchar(SDL_Surface *img);

int pixelSpacingHorizontal(SDL_Surface *img);

int pixelSpacingVertical(SDL_Surface *img);

void blockDetection_horizontal(SDL_Surface *img);

int average(SDL_Surface *img);

void blockDetection_vertical(SDL_Surface *img);

void CutColumn(SDL_Surface * img, int begin_line, int end_line);

int FindBlackPixelInColumn(SDL_Surface *img, int begin_line, int end_line, int start);

void DrawAColumn(SDL_Surface *img,int y, int x, int end_line);

int FindBlackPixel(SDL_Surface *img, int x);

void DrawInImage(SDL_Surface *img);

void DrawALine(SDL_Surface *img,int x);

void lines(SDL_Surface* img);

#endif