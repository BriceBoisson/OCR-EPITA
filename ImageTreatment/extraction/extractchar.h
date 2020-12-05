#ifndef _EXTRACTIONCHAR_H
#define _EXTRACTIONCHAR_H

#include "../Segmentation/segmentation.h"

void extractword(SDL_Surface* img,int x, int y);
int countwc(SDL_Surface* img);
void ReturnPoswc(SDL_Surface* img, int *tab);
void __extractword(SDL_Surface* img);
void __extractchar(SDL_Surface *img);
void extractchar(SDL_Surface *img, int x, int y);

#endif