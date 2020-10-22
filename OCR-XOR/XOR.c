#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define    RAND_MAX 1000000

float my_rand(void){
    return ((float)(rand() % 10000)/5000) - 1;
}

typedef struct Neural_Network_Cell Neural_Network_Cell;
struct Neural_Network_Cell{
    int nb_weight;
    double weights[100];
    double biais;
    double output;
    int fn;
};

Neural_Network_Cell Create_Cell(int nb_weight, int fn){
    Neural_Network_Cell cell;
    cell.nb_weight = nb_weight;
    cell.fn = fn;
    cell.biais = 0;
    cell.output = 0;
    for (int i = 0; i < nb_weight; i++){
        cell.weights[i] = 0;
    }
    return cell;
}

typedef struct Neural_Network_Layer Neural_Network_Layer;
struct Neural_Network_Layer{
    int nb_cells;
    Neural_Network_Cell cells[100];
};

Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight, int fn){
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    for (int i = 0; i < nb_cell; i++){
        layer.cells[i] = Create_Cell(nb_weight, fn);
    }
    return layer;
}

typedef struct Neural_Network Neural_Network;
struct Neural_Network{
    int nb_layers;
    Neural_Network_Layer layers[10];
};

double sigmoide(double val){
    return (1.0 / (1.0 + exp(-1.0 * val)));
}

double (*functions[]) (double) = {&sigmoide};

Neural_Network Initialisation(int train){
    Neural_Network network;
    network.nb_layers = 2;
    network.layers[0] = Create_Layer(2, 2, 0);
    network.layers[1] = Create_Layer(1, 2, 0);

    if (train){
        for(int i = 0; i < network.nb_layers; i++){
            for(int j = 0; j < network.layers[i].nb_cells; j++){
                network.layers[i].cells[j].biais = my_rand();
                for (int k = 0; k < network.layers[i].cells[j].nb_weight; k++){
                    network.layers[i].cells[j].weights[k] = my_rand();
                }
            }
        }
    }
    else{

    }
    return network;
}

double ForwardPass(double entries[], Neural_Network network){
    double output = 0.0;
    Neural_Network_Layer layer, last_layer;

    // First Layer treatment
    layer = network.layers[0];
    for(int i = 0; i < layer.nb_cells; i++){
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int j = 0; j < cell.nb_weight; j++){
            tmp = cell.weights[j]*entries[i];
        }
        network.layers[0].cells[i].output = functions[cell.fn](tmp);
    }

    // Other Layer treatment
    for(int i = 1; i < network.nb_layers; i++){
        layer = network.layers[i];
        last_layer = network.layers[i-1];
        for(int j = 0; j < layer.nb_cells; j++){
            Neural_Network_Cell cell = layer.cells[j];
            double tmp = cell.biais;
            for (int k = 0; k < cell.nb_weight; k++){
                tmp = cell.weights[k]*last_layer.cells[k].output;
            }
            network.layers[i].cells[j].output = functions[cell.fn](tmp);
            if(j == (layer.nb_cells - 1)){
                output = network.layers[i].cells[j].output;
            }
        }
    }
    return output;
}

void BackwardPass(/*a definir*/){
    
}

void training(/*a definir*/){

}

void XOR(){

}

int main(void){
    srand(time(NULL));
    printf("%f\n",my_rand());
    Neural_Network network = Initialisation(1);
    Neural_Network_Layer layer;
        for(int i = 0; i < network.nb_layers; i++){
            layer = network.layers[i];
            for(int j = 0; j < layer.nb_cells; j++){
                Neural_Network_Cell cell = layer.cells[j];
                printf("biais layer: %d cell: %d  :  %f\n",i, j, cell.biais);
                for (int k = 0; k < cell.nb_weight; k++){
                    printf("poid layer: %d cell: %d number: %d  :  %f\n",i, j, k, cell.biais);
                }
            }
        }
        printf("-------------------------------\n");
        double b[2] = {1.0,0.0};
        double a = ForwardPass(b, network);
        printf("%f\n", a);
        for(int i = 0; i < network.nb_layers; i++){
            layer = network.layers[i];
            for(int j = 0; j < layer.nb_cells; j++){
                Neural_Network_Cell cell = layer.cells[j];
                printf("biais layer: %d cell: %d  :  %f\n",i, j, cell.biais);
                for (int k = 0; k < cell.nb_weight; k++){
                    printf("poid layer: %d cell: %d number: %d  :  %f\n",i, j, k, cell.biais);
                }
            }
        }
    return 0;
}