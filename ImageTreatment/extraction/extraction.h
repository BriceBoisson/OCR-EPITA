#ifndef _EXTRACTION_H
#define _EXTRACTION_H

#include "../Segmentation/segmentation.h"
#include "../../XorToOCR/structure.h"

void extractpar(SDL_Surface* img,int x, int y, Neural_Network *network);
int countlinepar(SDL_Surface* img);
void ReturnPosPar(SDL_Surface* img, int *tab);
void __extractpar(SDL_Surface* img, Neural_Network *network);
void __extractline(SDL_Surface *img, Neural_Network *network);
void extractline(SDL_Surface *img, int x, int y, Neural_Network *network);

#endif