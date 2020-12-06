#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "structure.h"

Neural_Network Initialisation();
void ForwardPass(double entries[], Neural_Network *network);
void BackwardPass(double expected, double *entries,
                                            Neural_Network *network);

#endif
