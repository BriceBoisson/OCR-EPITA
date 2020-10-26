#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "init_neural_network.h"
#include "maths_functions.h"
#include "walkthrough.h"
#include "cost_function.h"
#include "training.h"

int main()
{
    srand(time(NULL));
    Neural_network nn;
    int input[2];
    input[0]=1;
    input[1]=0;
    nn = init_nn(input);
    nn = walkthrough(nn);
    double avCost = averageCost(5000);
    printf("averageCost = %f\n",avCost);
    trainingSession(nn,101534,46545654);
    avCost = averageCost(5000);
    printf("averageCost after training = %f\n",avCost);
    
}
