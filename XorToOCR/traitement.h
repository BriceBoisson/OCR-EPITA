#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "structure.h"

Neural_Network Initialisation();
Neural_Network ForwardPass(double entries[], Neural_Network network);
Neural_Network BackwardPass(double expected[], double entries[][2],
                                            Neural_Network network, int i_data);

#endif
