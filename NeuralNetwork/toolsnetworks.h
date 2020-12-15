#ifndef TOOLS__NETWORKS_H
#define TOOLS__NETWORKS_H

#include <SDL2/SDL.h>
#include "structure.h"


float my_rand(void);

void softmax(Neural_Network_Layer *layer);

char indiceToChar(int indice);

double sigmoid(double val);

double* imagetomatrix(char* str, int size);
double* segmentationtomatrix(SDL_Surface *loadedImage, int size);


#endif
