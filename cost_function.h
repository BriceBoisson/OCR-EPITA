#ifndef COST_FUNCTION_H
#define COST_FUNCTION_H

double costFunction(int inputs[2]);
int* generateInputs();
double averageCost(int trainingDuration);
int gradient(Neural_network nn, int y, double* dC);
int backpropagation(Neural_network nn, int inputs[2], int y, double rate);
#endif
