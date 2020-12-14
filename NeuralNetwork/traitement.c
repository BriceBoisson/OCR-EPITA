#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "toolsnetworks.h"
#include "training.h"
#include "structure.h"

#define NB_PIXEL 400
#define NB_OUTPUT 65
#define DELTA 0.2

// Fonctions de traitement du reseau de neurone : Initialisation, Forward et
// backpropagation.

Neural_Network Initialisation()
{
    Neural_Network network;
    network.nb_layers = 2;
    network.layers = (Neural_Network_Layer*)malloc(network.nb_layers*sizeof(Neural_Network_Layer));
    network.layers[0] = Create_Layer((int)NB_PIXEL * 2 /3, NB_PIXEL);
    network.layers[1] = Create_Layer(NB_OUTPUT, (int)NB_PIXEL * 2 / 3);
    network.output = 0.0;
    network.nboutput = NB_OUTPUT;
    
    for (int i = 0; i < network.nb_layers; i++)
    {
	for (int j = 0; j<network.layers[i].nb_cells; j++)
	{
	    network.layers[i].cells[j].biais = my_rand();
	    for (int k = 0; k < network.layers[i].cells[j].nb_weight; k++)
	    {
		network.layers[i].cells[j].weights[k] = my_rand();
	    }
	}
    }

    return network;
}

void ForwardPass(double entries[], Neural_Network *network)
{
    //Le passage de Xor à OCR est similaire pour le traitement du premier layer.
    Neural_Network_Layer layer, previous_layer;

    // First Layer treatment
    layer = (*network).layers[0];
    for(int i = 0; i < layer.nb_cells; i++)
    {
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int j = 0; j < cell.nb_weight; j++)
        {
            tmp += cell.weights[j] * entries[j];
        }


        (*network).layers[0].cells[i].output = sigmoid(tmp);
    }
	
    //Cette fois, on a plus qu'un noeud en output, donc plus de network.output en int,
    //mais on peut mettre un char à la place pour accéder au résultat renvoyé par notre réseau.
    // Output Layer treatment
    layer = (*network).layers[(*network).nb_layers-1];
    previous_layer = (*network).layers[0];
    for (int i = 0; i < layer.nb_cells; i++){
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int k = 0; k < cell.nb_weight; k++)
        {
            tmp += cell.weights[k]*previous_layer.cells[k].output;
        }

        (*network).layers[1].cells[i].output = tmp;
    }
 
    softmax(&layer);
    (*network).output = getIndiceMax(network);
}

void BackwardPass(double *expected, double *entries, 
                                            Neural_Network *network)
{
    for (int i = 0; i < network->nboutput; i++){
        double cell_output = (*network).layers[1].cells[i].output;
        double dCell_output = cell_output*(1-cell_output);
        double dError = (expected[i]-cell_output);
        
        for (int j = 0; j < (*network).layers[1].cells[i].nb_weight; j++)
        {
            double f = (*network).layers[0].cells[j].output;
            (*network).layers[1].cells[i].previous_dError[j] = (*network).layers[1].cells[i].weights[j] * dCell_output * dError;
            (*network).layers[1].cells[i].weights[j] += DELTA * f * dCell_output * dError;
        }
        (*network).layers[1].cells[i].biais += DELTA * dCell_output * dError;
    }



    for (int i = 0; i < (*network).layers[0].nb_cells; i++)
    {
        double cell_output = (*network).layers[0].cells[i].output;
        double dg = cell_output*(1-cell_output);
        double dError = 0;

        for (int j = 0; j < (*network).layers[1].nb_cells; j++){
            dError += (*network).layers[1].cells[j].previous_dError[i];
        }
        
        for (int j = 0; j < (*network).layers[0].cells[i].nb_weight; j++)
        {
            double f = entries[j];
            (*network).layers[0].cells[i].weights[j] += DELTA * f * dg * dError;
        }

        (*network).layers[0].cells[i].biais += DELTA * dg * dError;
    }
}
