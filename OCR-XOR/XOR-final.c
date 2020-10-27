#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float my_rand(void){
    return ((float)(rand() % 10000)/5000) - 1;
}

typedef struct Neural_Network_Cell Neural_Network_Cell;
struct Neural_Network_Cell{
    int nb_weight;
    double weights[100];
    double derivate_weights[10];
    double gradiant_weights[10];
    double gradiant_biais;
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
    cell.gradiant_biais = 0.0;
    for (int i = 0; i < nb_weight; i++){
        cell.weights[i] = 0.0;
        cell.derivate_weights[i] = 0.0;
        cell.gradiant_weights[i] = 0.0;
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
    int nb_entries;
    double output;
};

double sigmoide(double val){
    return (1.0 / (1.0 + exp(-1.0 * val)));
}

double derivate_sigmoide(double val){
    return (val * (1.0 - val));
}

double (*functions[]) (double) = {&sigmoide};

double (*derivate_functions[]) (double) = {&derivate_sigmoide};

Neural_Network Initialisation(int train){
    Neural_Network network;
    network.nb_layers = 2;
    network.layers[0] = Create_Layer(2, 2, 0);
    network.layers[1] = Create_Layer(1, 2, 0);
    network.nb_entries = 4;
    network.output = 0.0;

    network.layers[0].cells[0].biais = my_rand();
    network.layers[0].cells[1].biais = my_rand();
    network.layers[1].cells[0].biais = my_rand();
    network.layers[0].cells[0].weights[0] = my_rand();
    network.layers[0].cells[0].weights[1] = my_rand();
    network.layers[0].cells[1].weights[0] = my_rand();
    network.layers[0].cells[1].weights[1] = my_rand();
    network.layers[1].cells[0].weights[0] = my_rand();
    network.layers[1].cells[0].weights[1] = my_rand();

    /*if (train){
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

    }*/
    return network;
}

Neural_Network ForwardPass(double entries[], Neural_Network network){
    Neural_Network_Layer layer, last_layer;

    // First Layer treatment
    layer = network.layers[0];
    for(int i = 0; i < layer.nb_cells; i++){
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int j = 0; j < cell.nb_weight; j++){
            tmp += cell.weights[j]*entries[j];
        }
        network.layers[0].cells[i].output = functions[cell.fn](tmp);
    }

    // Output Layer treatment
    layer = network.layers[1];
    last_layer = network.layers[0];
    Neural_Network_Cell cell = layer.cells[0];
    double tmp = cell.biais;
    for (int k = 0; k < cell.nb_weight; k++){
        tmp += cell.weights[k]*last_layer.cells[k].output;
    }
    network.layers[1].cells[0].output = functions[cell.fn](tmp);
    network.output = network.layers[1].cells[0].output;

    return network;
}

Neural_Network BackwardPass(double expected[], double entries[][2], Neural_Network network, int i_data){
    double g = network.layers[1].cells[0].output;
    double dg = g*(1-g);
    double E = (expected[i_data]-g);
    for (int j = 0; j < network.layers[0].cells[0].nb_weight; j++){
        double f = network.layers[0].cells[j].output;
        network.layers[1].cells[0].derivate_weights[j] = dg * E;
        network.layers[1].cells[0].gradiant_weights[j] = f * dg * E;
        network.layers[1].cells[0].weights[j] += network.layers[1].cells[0].gradiant_weights[j];
    }
    network.layers[1].cells[0].gradiant_biais = dg * E;
    network.layers[1].cells[0].biais += network.layers[1].cells[0].gradiant_biais;

    for (int i = 0; i < network.layers[0].nb_cells; i++){
        double E = network.layers[1].cells[0].derivate_weights[i];
        double g = network.layers[0].cells[i].output;
        double dg = g*(1-g);
        for (int j = 0; j < network.layers[0].cells[i].nb_weight; j++){
            double f = entries[i_data][j];
            network.layers[0].cells[i].gradiant_weights[j] = network.layers[1].cells[0].weights[i] * f * dg * E;
            network.layers[0].cells[i].weights[j] += network.layers[0].cells[i].gradiant_weights[j];
        }
        network.layers[0].cells[i].gradiant_biais = network.layers[1].cells[0].weights[i] * dg * E;
        network.layers[0].cells[i].biais += network.layers[0].cells[i].gradiant_biais;
    }

    return network;
}

void training(/*a definir*/){

}

void XOR(){

}

Neural_Network try(Neural_Network network){
    return network;
}

int main(void){
    srand(time(NULL));
        double b[4][2] = {{0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0}};
        double c[4] = {0.0,1.0,1.0,0.0};
        double err = 1;
        while (err > 0.01){
            Neural_Network network = Initialisation(1);
            for (int i = 0; i < 2000; i++){
                for(int j = 0; j < 4; j++){
                    network = ForwardPass(b[j], network);
                    printf("entree : %f   %f  ->   %f\n", b[j][0], b[j][1], network.output);
                    err += ((c[j] - network.output) * (c[j] - network.output));
                    network = BackwardPass(c, b, network, j);
                    //printf("%f  %f  %f  %f  %f  %f  %f  %f  %f\n",network.layers[0].cells[0].weights[0], network.layers[0].cells[0].weights[1], network.layers[0].cells[0].biais, network.layers[0].cells[1].weights[0], network.layers[0].cells[1].weights[1], network.layers[0].cells[1].biais, network.layers[1].cells[0].weights[0], network.layers[1].cells[0].weights[1], network.layers[1].cells[0].biais);
                    //printf("err : %f\n", err);
                }
                err /= 4;
            }
        }
        printf("%f\n", err);

        /*Neural_Network_Layer layer;
        Neural_Network network2 = network;
        for(int i = 0; i < network2.nb_layers; i++){
            layer = network2.layers[i];
            for(int j = 0; j < layer.nb_cells; j++){
                Neural_Network_Cell cell = layer.cells[j];
                printf("biais layer: %d cell: %d  :  %f\n",i, j, cell.biais);
                for (int k = 0; k < cell.nb_weight; k++){
                    printf("poid layer: %d cell: %d number: %d  :  %f\n",i, j, k, cell.weights[k]);
                }
            }
        }*/

    return 0;
}