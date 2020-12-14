#ifndef TOOLS__NETWORKS_H
#define TOOLS__NETWORKS_H

#include <SDL2/SDL.h>
#include "structure.h"

float my_rand(void);
double sigmoid(double val);
void softmax(Neural_Network_Layer *layer);
char indiceToChar(int indice);
double* imagetomatrix(char* str, int size);
double *segmentationtomatrix(SDL_Surface *loadedImage, int size);

#endif
