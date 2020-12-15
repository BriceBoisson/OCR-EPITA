#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "structure.h"


void Initialisation(Neural_Network *network);

void ForwardPass(double entries[], Neural_Network *network);

void BackwardPass(double *expected, double *entries,
                                            Neural_Network *network);


#endif
