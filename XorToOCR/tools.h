#ifndef TOOLS_H
#define TOOLS_H

#include "structure.h"

float my_rand(void);
double sigmoid(double val);
void softmax(Neural_Network_Layer *layer, double somme);
double generateChar(void);
double* imagetomatrix(char* str, int size);

#endif
