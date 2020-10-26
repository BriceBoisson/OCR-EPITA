#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//TO-DO next : backpropagation -> derivative of cost by weights


double sigmoid(double n)
{
    return 1/(1+exp(-n));
}

double primeSigmoid(double n)
{
    return (1/(1+ exp(-n))*(1-(1/(1 + exp(-n)))));
}

int expectedResult(int a, int b)
{
    int y;
    if (a==b)
    {
        y = 0;
    }
    else
    {
        y = 1;
    }
    return y;
}

double walkthrough(int* inputs, double* layer, double weights_input_to_layer[2][3],
                double weights_layer_to_output[3][1], double* biais_layer,
                double* biais_output, double* output, double* z)
{
    //gets the size of the arrays layer and inputs
    int len_layer = sizeof(*layer)/sizeof(int)+1;
    int len_inputs = sizeof(*inputs)/sizeof(int)+1;
    int len_outputs = sizeof(*output)/sizeof(int)+1;
    double c;
    //printf("len_inputs : %i\n", len_inputs);
    //printf("len_layer : %i\n", len_layer);
    //sums the (value of input * weigh of input to layer.node) for each node in 
    //the hidden layer
    for (int i = 0; i<len_layer; i++)
    {
        c = 0;
        for (int j = 0; j<len_inputs;j++)
        {
            c+= inputs[j]*weights_input_to_layer[j][i];
            //~ printf("weights(%i)(%i)=%f\n",j,i,weights_input_to_layer[j][i]);
            
        }
        layer[i] = sigmoid(c + biais_layer[i]);
        //~ printf("layer[i] = %f\n",layer[i]);
    }
    c=0;
    //sums the (value of layer.node * weigh of layer.node to output)
    for (int i = 0; i< len_outputs;i++ )
    {
        for (int j = 0; j<len_layer;j++)
        {
            c+= layer[j]*weights_layer_to_output[j][i];
        }
        z[i]=(c + biais_output[i]);
        output[i]= sigmoid(z[i]);
        //~ printf(" z = %f\n",z[i]);
        //~ printf(" output = %f\n",output[i]);
    }
    //returns the value of output[0]
    //~ printf(" output = %f\n",output[0]);
    return output[0];
}

double* costDerivative( int trainingData[15][3] , double* layer, double weights_input_to_layer[2][3],
                        double weights_layer_to_output[3][1], double* biais_layer, 
                        double* biais_output, double* output,
                        double* z)
{
    int len_outputs = sizeof(*output)/sizeof(int)+1;
    int len_trainingData = sizeof(**trainingData)/sizeof(int*)+1;
    double *costDerivated = malloc (sizeof (double)*len_outputs);
    for (int i=0; i<len_trainingData;i++)
    {
        int inputs[2];
        for (int k = 0; k<2; k++)
        {
            inputs[k]=trainingData[i][k];
        }
        int y = trainingData[i][len_trainingData];
        for (int j = 0; j<len_outputs; j++)
        {
            walkthrough(inputs, layer, weights_input_to_layer,
                        weights_layer_to_output, biais_layer, biais_output,
                        output, z);
            costDerivated[j]+=2*(output[j]-y)*primeSigmoid(z[j])*layer[j];
        }
        printf("costDerivated[0] = %f\n", costDerivated[0]);
    }
    return costDerivated;
    
}


double costFunction(int* inputs, double* layer, double 
                weights_input_to_layer[2][3], double 
                weights_layer_to_output[3][1], double* biais_layer,
                double* biais_output, double* output, double* z)
{
    int y = expectedResult(inputs[0], inputs[1]);
    return pow(walkthrough(inputs, layer, weights_input_to_layer,
                        weights_layer_to_output, biais_layer, biais_output,
                        output, z)-y,2);
    
}




int main(int argc, char** argv)
{
    //checks that there are enough arguments(=inputs) and then add them to a new
    //array called inputs
    if (argc != 3)
    {
        errx(1, "Error");
    }
    int inputs[2];
    inputs[0] = atoi(argv[1]);
    inputs[1] = atoi(argv[2]);
    srand(time(NULL));
    
    //initializes an array representing the hidden layer, and sets each node's
    //value to a random number between 0.0 and 0.1. Also initializes the z array
    //used to calculate the sigmoid later on.
    double layer[3];
    double biais_layer[3];
    double z[3];
    for (int i=0;i<3;i++)
    {
        layer[i] = rand()/(double)RAND_MAX;
        z[i] = 0;
        biais_layer[i] = rand()/(double)RAND_MAX;
    }
    
    //same with outputs. We now have all our layers set
    double output[1];
    double biais_output[1];
    biais_output[0] = rand()/(double)RAND_MAX;
    
    // Initializes a matrix containing the weights of the links from the inputs
    // to the hidden layer, then sets their values to a random number again.
    // weights_layer1_layer2_[a][b] : a nb of nodes in layer1, b number of nodes
    // in layer2.
    double weights_input_to_layer[2][3];
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            weights_input_to_layer[i][j] = rand()/(double)RAND_MAX;
            //printf("weights(%i)(%i)=%f\n",i,j,weights_input_to_layer[i][j]);
        }
    }
    //same as before, but from the hidden layer to the output.
    double weights_layer_to_output[3][1];
    for(int i = 0; i <= 3; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            weights_layer_to_output[i][j] = rand()/(double)RAND_MAX;
        }
    }
    
    double cost = costFunction(inputs, layer, weights_input_to_layer,
                        weights_layer_to_output, biais_layer, biais_output,
                        output, z);
    printf("cost = %f\n",cost);
    
    int trainingData[15][3];
    for (int i = 0; i<15; i++)
    {
        trainingData[i][0] = (rand() % 100 + 1)%2;
        trainingData[i][1] = (rand() % 100 + 1)%2;
        trainingData[i][2] = expectedResult(trainingData[i][0],trainingData[i][1]);
        
    }
    
    costDerivative(trainingData, layer, weights_input_to_layer,
                        weights_layer_to_output, biais_layer, 
                         biais_output,output,
                         z);
    
    return 0;
}


