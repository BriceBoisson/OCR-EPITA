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
    double derivate_weights[10][10];
    double gradiant_weights[10][10];
    double gradiant_biais[10];
    double biais;
    double output;
    double outputs[10];
    double derivate_outputs[10];
    int fn;
};

Neural_Network_Cell Create_Cell(int nb_weight, int nb_entries, int fn){
    Neural_Network_Cell cell;
    cell.nb_weight = nb_weight;
    cell.fn = fn;
    cell.biais = 0;
    cell.output = 0;
    for (int i = 0; i < nb_entries; i++){
        cell.outputs[i] = 0.0;
        cell.derivate_outputs[i] = 0.0;
        cell.gradiant_biais[i] = 0.0;
    }
    for (int i = 0; i < nb_weight; i++){
        cell.weights[i] = 0.0;
        for (int j = 0; j < nb_entries; j++){
            cell.derivate_weights[i][j] = 0.0;
            cell.gradiant_weights[i][j] = 0.0;
        }
    }
    return cell;
}

typedef struct Neural_Network_Layer Neural_Network_Layer;
struct Neural_Network_Layer{
    int nb_cells;
    Neural_Network_Cell cells[100];
};

Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight, int nb_entries, int fn){
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    for (int i = 0; i < nb_cell; i++){
        layer.cells[i] = Create_Cell(nb_weight, nb_entries, fn);
    }
    return layer;
}

typedef struct Neural_Network Neural_Network;
struct Neural_Network{
    int nb_layers;
    Neural_Network_Layer layers[10];
    int nb_entries;
    double outputs[10];
};

double sigmoide(double val){
    return (1.0 / (1.0 + exp(-1.0 * val)));
}

double derivate_sigmoide(double val){
    return ( exp(-1.0 * val) / ( (1.0 + exp(-1.0 * val))*(1.0 + exp(-1.0 * val)) ) );
}

double (*functions[]) (double) = {&sigmoide};

double (*derivate_functions[]) (double) = {&derivate_sigmoide};

Neural_Network Initialisation(int train){
    Neural_Network network;
    network.nb_layers = 2;
    network.layers[0] = Create_Layer(2, 2, 4, 0);
    network.layers[1] = Create_Layer(1, 2, 4, 0);
    network.nb_entries = 4;
    for (int i = 0; i < network.nb_entries; i++){
        network.outputs[i] = 0.0;
    }

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

Neural_Network ForwardPass(Neural_Network network, int iteration){
    /*double output = 0.0;
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
        network.layers[0].cells[i].outputs[iteration] = functions[cell.fn](tmp);
        network.layers[0].cells[i].derivate_outputs[iteration] = derivate_functions[cell.fn](tmp);
    }

    // Other Layer treatment
    /*for(int i = 1; i < network.nb_layers; i++){
        layer = network.layers[i];
        last_layer = network.layers[i-1];
        for(int j = 0; j < layer.nb_cells; j++){
            Neural_Network_Cell cell = layer.cells[j];
            double tmp = cell.biais;
            for (int k = 0; k < cell.nb_weight; k++){
                tmp = cell.weights[k]*last_layer.cells[k].output;
            }
            network.layers[i].cells[j].output = functions[cell.fn](tmp);
            network.layers[i].cells[j].outputs[iteration] = functions[cell.fn](tmp);
            network.layers[i].cells[j].derivate_outputs[iteration] = derivate_functions[cell.fn](tmp);
            if(j == (layer.nb_cells - 1)){
                output = network.layers[i].cells[j].output;
                network.outputs[iteration] = output;
            }
        }
    }*/
    return network;
}

Neural_Network BackwardPass(double expected[], double entries[][2], Neural_Network network){
    for (int iteration = 0; iteration < network.nb_entries; iteration++){

        for (int i = 0; i < network.layers[network.nb_layers-1].nb_cells; i++){
            double F = network.outputs[iteration];
            for (int j = 0; j < network.layers[network.nb_layers-1].cells[i].nb_weight; j++){
                double f = network.layers[network.nb_layers-2].cells[j].outputs[iteration];
                //double g = network.layers[network.nb_layers-1].cell[i].outputs[iteration];
                double g_prime = network.layers[network.nb_layers-1].cells[i].derivate_outputs[iteration];
                network.layers[network.nb_layers-1].cells[i].derivate_weights[j][iteration] = f * g_prime;
                network.layers[network.nb_layers-1].cells[i].gradiant_weights[j][iteration] = 2.0 * f * g_prime * (F - expected[iteration]);
            }
            network.layers[network.nb_layers-1].cells[i].gradiant_biais[iteration] = 2.0 * network.layers[network.nb_layers-1].cells[i].derivate_outputs[iteration] * (F - expected[iteration]);
        }

        for(int k = network.nb_layers-2; k > 0; k++){
            for (int i = 0; i < network.layers[k].nb_cells; i++){
                double weight_partial = 0.0;
                for (int l = 0; l < network.layers[k+1].nb_cells; l++){
                    weight_partial += (network.layers[k+1].cells[l].derivate_weights[i][iteration] * network.layers[k+1].cells[l].weights[i]);
                }
                weight_partial /= network.layers[k+1].nb_cells;
                double g = network.layers[k].cells[i].outputs[iteration];
                double g_prime = network.layers[k].cells[i].derivate_outputs[iteration];
                double F = network.outputs[iteration];
                for (int j = 0; j < network.layers[k].cells[i].nb_weight; j++){
                    double f = network.layers[k-1].cells[j].outputs[iteration];
                    network.layers[k].cells[i].derivate_weights[j][iteration] = ((f * g_prime * weight_partial) / g);
                    network.layers[k].cells[i].gradiant_weights[j][iteration] = 2.0 * ((f * g_prime * weight_partial) / g) * (F - expected[iteration]);
                }
                network.layers[k].cells[i].gradiant_biais[iteration] = 2.0 * ((g_prime * weight_partial) / g) * (F - expected[iteration]);
            }
        }

            for (int i = 0; i < network.layers[0].nb_cells; i++){
                double weight_partial = 0.0;
                for (int l = 0; l < network.layers[1].nb_cells; l++){
                    weight_partial += (network.layers[1].cells[l].derivate_weights[i][iteration] * network.layers[1].cells[l].weights[i]);
                }
                weight_partial /= network.layers[1].nb_cells;
                double g = network.layers[0].cells[i].outputs[iteration];
                double g_prime = network.layers[0].cells[i].derivate_outputs[iteration];
                double F = network.outputs[iteration];
                for (int j = 0; j < network.layers[0].cells[i].nb_weight; j++){
                    double f = entries[iteration][j];
                    network.layers[0].cells[i].derivate_weights[j][iteration] = ((f * g_prime * weight_partial) / g);
                    network.layers[0].cells[i].gradiant_weights[j][iteration] = 2.0 * ((f * g_prime * weight_partial) / g) * (F - expected[iteration]);
                }
                network.layers[0].cells[i].gradiant_biais[iteration] = 2.0 * ((g_prime * weight_partial) / g) * (F - expected[iteration]);
            }
    }

        for(int i = 0; i < network.nb_layers; i++){
            for(int j = 0; j < network.layers[i].nb_cells; j++){
                double tmp = 0;
                for (int l = 0; l < network.nb_entries; l++){
                    tmp += network.layers[i].cells[j].gradiant_biais[l];
                }
                network.layers[i].cells[j].biais = (tmp / network.nb_entries);
                for (int k = 0; k < network.layers[i].cells[j].nb_weight; k++){
                    double tmp = 0;
                    for (int l = 0; l < network.nb_entries; l++){
                        tmp += network.layers[i].cells[j].gradiant_weights[k][l];
                    }
                    network.layers[i].cells[j].weights[k] = (tmp / network.nb_entries);
                }
            }
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
    //printf("%f\n",my_rand());
    Neural_Network network = Initialisation(1);
    Neural_Network_Layer layer;
     Neural_Network network2 = try(network);
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
        double b[4][2] = {{1.0,0.0},{1.0,1.0},{0.0,1.0},{0.0,0.0}};
        double c[4] = {0.0,1.0,0.0,1.0};
       
        /*network = ForwardPass(b[1], network, 1);
        network = ForwardPass(b[2], network, 2);
        network = ForwardPass(b[3], network, 3);
        network = BackwardPass(c, b, network);
        //printf("%f\n", a);
        for(int i = 0; i < network.nb_layers; i++){
            layer = network.layers[i];
            for(int j = 0; j < layer.nb_cells; j++){
                Neural_Network_Cell cell = layer.cells[j];
                printf("biais layer: %d cell: %d  :  %f\n",i, j, cell.biais);
                for (int k = 0; k < cell.nb_weight; k++){
                    printf("poid layer: %d cell: %d number: %d  :  %f\n",i, j, k, cell.biais);
                }
            }
        }*/
    return 0;
}