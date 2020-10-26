#ifndef INIT_NEURAL_NETWORK_H
#define INIT_NEURAL_NETWORK_H

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

Neural_network init_weights(Neural_network neural_network);
Neural_network init_nn (int* inputs);

#endif
