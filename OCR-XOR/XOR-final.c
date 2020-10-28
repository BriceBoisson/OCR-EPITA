#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definition des fonctions de type outils
float my_rand(void){
    return ((float)(rand() % 10000)/5000) - 1;
}

double sigmoid(double val){
    return (1.0 / (1.0 + exp(-1.0 * val)));
}

// Definition des structure du reseau de neurone
typedef struct Neural_Network_Cell Neural_Network_Cell;
struct Neural_Network_Cell{
    int nb_weight;
    double weights[100];
    double previous_dError[10];
    double biais;
    double output;
};

Neural_Network_Cell Create_Cell(int nb_weight){
    Neural_Network_Cell cell;
    cell.nb_weight = nb_weight;
    cell.biais = 0;
    cell.output = 0;
    for (int i = 0; i < nb_weight; i++){
        cell.weights[i] = 0.0;
        cell.previous_dError[i] = 0.0;
    }
    return cell;
}

typedef struct Neural_Network_Layer Neural_Network_Layer;
struct Neural_Network_Layer{
    int nb_cells;
    Neural_Network_Cell cells[100];
};

Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight){
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    for (int i = 0; i < nb_cell; i++){
        layer.cells[i] = Create_Cell(nb_weight);
    }
    return layer;
}

typedef struct Neural_Network Neural_Network;
struct Neural_Network{
    int nb_layers;
    Neural_Network_Layer layers[10];
    double output;
};

// Fonction de traitement du reseau de neurone
Neural_Network Initialisation(){
    Neural_Network network;
    network.nb_layers = 2;
    network.layers[0] = Create_Layer(2, 2);
    network.layers[1] = Create_Layer(1, 2);
    network.output = 0.0;

    for(int i = 0; i < network.nb_layers; i++){
        for(int j = 0; j < network.layers[i].nb_cells; j++){
            network.layers[i].cells[j].biais = my_rand();
            for (int k = 0; k < network.layers[i].cells[j].nb_weight; k++){
                network.layers[i].cells[j].weights[k] = my_rand();
            }
        }
    }

    return network;
}

Neural_Network ForwardPass(double entries[], Neural_Network network){
    Neural_Network_Layer layer, previous_layer;

    // First Layer treatment
    layer = network.layers[0];
    for(int i = 0; i < layer.nb_cells; i++){
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int j = 0; j < cell.nb_weight; j++){
            tmp += cell.weights[j]*entries[j];
        }
        network.layers[0].cells[i].output = sigmoid(tmp);
    }

    // Output Layer treatment
    layer = network.layers[1];
    previous_layer = network.layers[0];
    Neural_Network_Cell cell = layer.cells[0];
    double tmp = cell.biais;
    for (int k = 0; k < cell.nb_weight; k++){
        tmp += cell.weights[k]*previous_layer.cells[k].output;
    }
    network.layers[1].cells[0].output = sigmoid(tmp);
    network.output = network.layers[1].cells[0].output;

    return network;
}

Neural_Network BackwardPass(double expected[], double entries[][2], Neural_Network network, int i_data){

    double cell_output = network.layers[1].cells[0].output;
    double dCell_output = cell_output*(1-cell_output);
    double dError = (expected[i_data]-cell_output);
    for (int j = 0; j < network.layers[0].cells[0].nb_weight; j++){
        double f = network.layers[0].cells[j].output;
        network.layers[1].cells[0].previous_dError[j] = dCell_output * dError;
        network.layers[1].cells[0].weights[j] += f * dCell_output * dError;
    }
    network.layers[1].cells[0].biais += dCell_output * dError;

    for (int i = 0; i < network.layers[0].nb_cells; i++){
        double cell_output = network.layers[0].cells[i].output;
        double dg = cell_output*(1-cell_output);
        double dError = network.layers[1].cells[0].previous_dError[i];
        for (int j = 0; j < network.layers[0].cells[i].nb_weight; j++){
            double f = entries[i_data][j];
            dError *= network.layers[1].cells[0].weights[i];
            network.layers[0].cells[i].weights[j] += f * dg * dError;
        }
        network.layers[0].cells[i].biais += dg * dError;
    }

    return network;
}

// Fonction d'utilisation
Neural_Network training(){
    printf("Waiting for training\n");
    Neural_Network network;
    double b[4][2] = {{0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0}};
    double c[4] = {0.0,1.0,1.0,0.0};
    double err = 1.0;
    
    while (err > 0.01){
        network = Initialisation();
        for (int i = 0; i < 2000; i++){
            for(int j = 0; j < 4; j++){
                network = ForwardPass(b[j], network);
                err += ((c[j] - network.output) * (c[j] - network.output));
                network = BackwardPass(c, b, network, j);
            }
            err /= 4;
        }
    }
    
    printf("Erreur : %f\n", err);

    return network;
}

void XOR(Neural_Network network){
    double args[2] = {0.0, 0.0};

    printf("XOR entries : ");
    scanf("%lf %lf", &args[0], &args[1]);
    network = ForwardPass(args, network);
    printf("result : %f", network.output);
}

Neural_Network try(Neural_Network network){
    return network;
}

int main(void){
    srand(time(NULL));

    Neural_Network network = training();

    XOR(network);

    return 0;
}