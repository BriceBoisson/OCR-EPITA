#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "traitement.h"
#include "toolsnetworks.h"
#include "training.h"
#include "structure.h"

// Definition des structure du reseau de neurone

Neural_Network_Cell Create_Cell(int nb_weight)
{
    Neural_Network_Cell cell;
    cell.nb_weight = nb_weight;
    cell.biais = 0;
    cell.output = 0;
    cell.weights = (double*)calloc(nb_weight, sizeof(double));
    cell.previous_dError = (double*)calloc(nb_weight, sizeof(double));
    return cell;
}


Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight)
{
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    layer.cells = (Neural_Network_Cell*)malloc(nb_weight*sizeof(Neural_Network_Cell));
    for (int i = 0; i < nb_weight; i++){
        *(layer.cells + i) = Create_Cell(nb_weight);
    }
    return layer;
}

void Free_Network(Neural_Network *network){
    for (int i = 0; i < network->nb_layers; i++)
    {
        for (int j = 0; j < network->layers[i].nb_cells; j++)
        {
            free(network->layers[i].cells[j].weights);
            free(network->layers[i].cells[j].previous_dError);
        }
        free(network->layers[i].cells);
    }
    free(network->layers);
}

int getIndiceMax(Neural_Network *network){
    Neural_Network_Layer layer = network->layers[network->nb_layers-1];
    int i_max = 0;
    for (int i = 0; i < layer.nb_cells; i++)
    {
        if (layer.cells[i].output > layer.cells[i_max].output){
            i_max = i;
        }
    }
    return i_max;
}

int Save_Network(Neural_Network *network){
    printf("%f", network->output);
    /*FILE *fichier;

    if (!mkdir('src/SaveNeuralNetwork', 0777)){
        return 1;
    }
    for (int i = 0; i < network->nb_layers; i++)
    {
        char* str = concat('src/SaveNeuralNetwork/Layer-', i);
        if (!mkdir(str, 0777)){
            return 1;
        }
        for (int j = 0; j < network->layers[i].nb_cells; j++){
            if (!mkdir('src/SaveNeuralNetwork/Layer-' + i + '-cell-' + j, 0777)){
                return 1;
            }
            fichier = fopen('src/SaveNeuralNetwork/Layer-' + i + '-cell-' + j + "biais", "w");
            if (!fichier){
                return 1;
            }
            fprintf(fichier, "%f\n",network->layers[i].cells[j].biais);
            fclose(fichier);
            for (int k = 0; k < network->layers[i].cells[j].nb_weight; k++)
            {
                fichier = fopen('src/SaveNeuralNetwork/Layer-' + i + '-cell-' + j + "weight-" + k, "w");
                if (!fichier){
                    return 1;
                }
                fprintf(fichier, "%f\n",network->layers[i].cells[j].weights[k]);
                fclose(fichier);
            }
        }
    }*/

    return 0;
}

int Load_Network(Neural_Network *network){
    printf("%f", network->output);
    /*FILE *fichier;

    for (int i = 0; i < network->nb_layers; i++)
    {
        for (int j = 0; j < network->layers[i].nb_cells; j++){
            fichier = fopen('src/SaveNeuralNetwork/Layer-' + i + '-cell-' + j + "biais", "r");
            if (!fichier){
                return 1;
            }
            fprintf(fichier, "%f\n",network->layers[i].cells[j].biais);
            fclose(fichier);
            for (int k = 0; k < network->layers[i].cells[j].nb_weight; k++)
            {
                fichier = fopen('src/SaveNeuralNetwork/Layer-' + i + '-cell-' + j + "weight-" + k, "r");
                if (!fichier){
                    return 1;
                }
                fprintf(fichier, "%f\n",network->layers[i].cells[j].weights[k]);
                fclose(fichier);
            }
        }
    }*/

    return 0;
}