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
    cell.weights = (double*)malloc(nb_weight * sizeof(double));
    cell.previous_dError = (double*)malloc(nb_weight * sizeof(double));
    return cell;
}


Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight)
{
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    layer.cells = (Neural_Network_Cell*)
                            malloc(nb_cell * sizeof(Neural_Network_Cell));
    
    for (int i = 0; i < nb_cell; i++)
    {
        *(layer.cells + i) = Create_Cell(nb_weight);
    }
    return layer;
}

void Free_Network(Neural_Network *network)
{
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
    free(network);
}

int getIndiceMax(Neural_Network *network)
{
    Neural_Network_Layer layer = network->layers[network->nb_layers-1];
    int i_max = 0;
    for (int i = 0; i < layer.nb_cells; i++)
    {
        if (layer.cells[i].output > layer.cells[i_max].output)
            i_max = i;
    }
    return i_max;
}

int Save_Network(Neural_Network *network, char* filename)
{
    FILE *file;
    char path[100];
    sprintf(path, "src/SaveNeuralNetwork/%s", filename);
    file = fopen(path,"w");

    if (!file)
        return 0;
    
    for (int i = 0; i<network->nb_layers;i++)
    {
        int nb_c = network->layers[i].nb_cells;
        
        for (int j = 0; j < nb_c; j++)
        {
            int nb_w = network->layers[i].cells[j].nb_weight;
            
            for (int k = 0 ; k < nb_w;k++)
            {
                fprintf(file,"%f\n",network->layers[i].cells[j].weights[k]);
            }
            
            fprintf(file,"%f\n",network->layers[i].cells[j].biais);
        }
    }
    
    fclose(file);
    return 1;
}

int Load_Network(Neural_Network *network, char* filename)
{
    FILE *file;
    char path[100];
    sprintf(path, "src/SaveNeuralNetwork/%s", filename);
    file = fopen(path,"r");

    if (!file)
        return 0;
    
    char* cvalue = calloc(128,sizeof(char));
    double value;
    char* ptr;

    for (int i = 0; i < network->nb_layers; i++)
    {
        int nb_c = network->layers[i].nb_cells;

        for (int j = 0; j < nb_c; j++)
        {
            int nb_w = network->layers[i].cells[j].nb_weight;
            
            for (int k = 0 ; k < nb_w; k++)
            {
                
                fgets(cvalue, 128, file);
                value = strtod(cvalue, &ptr);
                network->layers[i].cells[j].weights[k] = value;
            }
            
            fgets(cvalue,128,file);
            value = strtod(cvalue,&ptr);
            network->layers[i].cells[j].biais = value;
        }
    }

    free(cvalue);
    return 1;
}
