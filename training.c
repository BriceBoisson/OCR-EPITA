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


int inputs[2];


//training part!

int trainingSession(Neural_network nn, int sessionDuration, double rate)
{
    //~ double dC[len_inputs*len_layer+len_layer*len_outputs];

    for (int k = 0; k<sessionDuration;k++)
    {
        generateInputs();
        nn.input[0]=inputs[0];
        nn.input[1]=inputs[1];
        //~ gradient(nn,expectedResult(nn.input[0],nn.input[1]),dC);
        //~ for (int i =0; i< len_inputs;i++)
        //~ {
            //~ for (int j = 0; j<len_layer;j++)
            //~ {
                //~ nn.weights_input_to_layer[i][j] += dC[i+j];
            //~ }
            
        //~ }
        
        //~ for (int i =0; i< len_layer;i++)
        //~ {
            //~ for (int j = 0; j<len_outputs;j++)
            //~ {
                //~ nn.weights_layer_to_output[i][j] += dC[i+j+len_inputs*len_layer];
            //~ }
            
        //~ }
        backpropagation(nn, inputs, expectedResult(nn.input[0],nn.input[1]),rate);
    }
    return EXIT_SUCCESS;
    
}
