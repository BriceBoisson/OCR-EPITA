#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "init_neural_network.h"
#include "maths_functions.h"
#include "walkthrough.h"
    
int inputs[2];

double costFunction(int inputs[2], Neural_network nn)
{
    //calcul le coût pour un set d'inputs donné
    double cost;
    int y;
    nn.input[0]=inputs[0];
    nn.input[1]=inputs[1];
    nn = walkthrough(nn);
    y = expectedResult(nn.input[0],nn.input[1]);
    cost=pow(nn.output[0]-y,2);
    return cost;
}

int* generateInputs()
{
    inputs[0] = rand()%2;
    inputs[1] = rand()%2;
    return inputs;
}

double averageCost(int trainingDuration, Neural_network nn)
{    
    double avCost;
    avCost = 0;
    for (int i=0; i<trainingDuration;i++)
    {
        
        generateInputs();
        avCost += costFunction(inputs,nn);
    }
    
    return avCost/trainingDuration;
}

Neural_network backpropagation(Neural_network nn, int inputs[2], int y, double rate)
{
    int len_layer = sizeof(nn.layer)/sizeof(double);
    int len_inputs = sizeof(nn.input)/sizeof(int);
    int len_outputs = sizeof(nn.output)/sizeof(double);
    
    for (int i = 0; i<len_layer;i++)
    {
        double totalError = 0;
        for (int j = 0; j<len_outputs;j++)
        {
            double errorD = errorFuncD(nn.output[j],y);
            double sigmoidD = primeSigmoid(nn.output[j]);
            totalError+= errorD * sigmoidD * nn.biais[j*len_layer+i];
            nn.biais[j*len_layer+i]-= rate * totalError * sigmoidD * nn.layer[i];
        }
        
        for (int j=0; j<len_inputs;j++)
        {
            nn.weights[i*len_inputs+j] -= rate * totalError * primeSigmoid(nn.layer[i]) * inputs[j];
        }
    }
    return nn;
}
