#ifndef _EXTRACTION_H
#define _EXTRACTION_H

#include "../Segmentation/segmentation.h"

void extractpar(SDL_Surface* img,int x, int y);
int countlinepar(SDL_Surface* img);
void ReturnPosPar(SDL_Surface* img, int *tab);
void __extractpar(SDL_Surface* img);
void __extractline(SDL_Surface *img);
void extractline(SDL_Surface *img, int x, int y);

#endif