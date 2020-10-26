#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "init_neural_network.h"
#include "maths_functions.h"

Neural_network walkthrough(Neural_network nn)
{
    int len_layer = sizeof(nn.layer)/sizeof(double);
    int len_inputs = sizeof(nn.input)/sizeof(int);
    int len_outputs = sizeof(nn.output)/sizeof(double);
    double c;
    
    //sums the (value of input * weigh of input to layer.node) for each node
    //in the hidden layer
    for (int i = 0; i<len_layer; i++)
    {
        c = 0;
        for (int j = 0; j<len_inputs;j++)
        {
            c+= nn.input[j]*nn.weights[i];
            
        }
        nn.layer[i] = sigmoid(c + nn.biais[i]);
    }
    c=0;
    //sums the (value of layer.node * weigh of layer.node to output)
    for (int i = 0; i< len_outputs;i++ )
    {
        for (int j = 0; j<len_layer;j++)
        {
            c+= nn.layer[j]*nn.weights[i+len_layer];
        }
        nn.z[i]=(c + nn.biais[i+len_layer]);
        nn.output[i]= sigmoid(nn.z[i]);
    }
    
    return nn;
    //~ for (int i=0; i<len_layer;i++)
    //~ {
        //~ c = 0;
        //~ for(int j=0; j<len_inputs;j++)
        //~ {
            //~ c += nn.input[j] * nn.weights[i * len_inputs +j];
        //~ }
        //~ nn.layer[i] = sigmoid(c+nn.biais[i]);
        
    //~ }
    
    //~ for (int i=0; i<len_outputs;i++)
    //~ {
        //~ c=0;
        //~ for (int j = 0; j<len_layer; j++)
            //~ c += nn.layer[j]*nn.biais[i*len_layer +j];
        //~ nn.output[i]= sigmoid(c + nn.biais[i+len_layer]);
        
    //~ }
    //~ return nn;
}
