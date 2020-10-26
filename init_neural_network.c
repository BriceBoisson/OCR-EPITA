#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct  {
    int input[2];
    double layer[3];
    //~ double biais_layer[3];
    double z[3];
    double output[1];
    //~ double biais_output[1];
    //~ double weights_input_to_layer[2][3];
    //~ double weights_layer_to_output[3][1];
    double weights [9];
    double biais[3+1];
} Neural_network;

Neural_network init_weights(Neural_network neural_network)
{
    //initializes the weights of 
    //~ for(int i = 0; i < 2; i++)
    //~ {
        //~ for(int j = 0; j < 3; j++)
        //~ {
            //~ neural_network.weights_input_to_layer[i][j] = rand()/(double)RAND_MAX;
        //~ }
    //~ }
    
    //~ for(int i = 0; i < 3; i++)
    //~ {
        //~ for(int j = 0; j < 1; j++)
        //~ {
            //~ neural_network.weights_layer_to_output[i][j] = rand()/(double)RAND_MAX;
                    //~ }
    //~ }
    
    for (int i=0; i<9; i++)
    {
        neural_network.weights[i] = rand()/(double)RAND_MAX;
    }
    return neural_network;
}


Neural_network init_nn (int* inputs)
{
    
    //initializes an array representing the hidden layer, and sets each node's
    //value to a random number between 0.0 and 0.1. Also initializes the z array
    //used to calculate the sigmoid later on.
    Neural_network nn;
    
    for (int i=0; i<2; i++)
    {
        nn.input[i] = inputs[i];
    }
    for (int i=0;i<3;i++)
    {
        nn.layer[i] = rand()/(double)RAND_MAX;
        nn.z[i] = 0;
        nn.biais[i] = rand()/(double)RAND_MAX;
    }
    
    //same with outputs. We now have all our layers set
    nn.biais[3] = rand()/(double)RAND_MAX;
    nn = init_weights(nn);
    return nn;
}
