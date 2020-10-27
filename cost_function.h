#ifndef COST_FUNCTION_H
#define COST_FUNCTION_H

double costFunction(int inputs[2]);
int* generateInputs();
double averageCost(int trainingDuration, Neural_network nn);
int gradient(Neural_network nn, int y, double* dC);
Neural_network backpropagation(Neural_network nn, int inputs[2], int y, double rate);
#endif
