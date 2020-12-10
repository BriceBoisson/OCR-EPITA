#ifndef _EXTRACTIONCHAR_H
#define _EXTRACTIONCHAR_H

#include "../Segmentation/segmentation.h"
#include "../../XorToOCR/structure.h"
#include "../../XorToOCR/traitement.h"
#include "../../XorToOCR/toolsnetworks.h"

void extractword(SDL_Surface* img,int x, int y,Neural_Network *network);
int countwc(SDL_Surface* img);
void ReturnPoswc(SDL_Surface* img, int *tab);
void __extractword(SDL_Surface* img, Neural_Network *network);
void __extractchar(SDL_Surface *img,Neural_Network *network);
void extractchar(SDL_Surface *img, int x, int y, Neural_Network *network);

#endif