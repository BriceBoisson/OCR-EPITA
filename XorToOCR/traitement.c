#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"


// Fonctions de traitement du reseau de neurone : Initialisation, Forward et
// backpropagation.

Neural_Network Initialisation()
{
    Neural_Network network;
    network.layers[0] = Create_Layer((int)nbpixels * 2 /3, nbpixels);
    network.layers[1] = Create_Layer(63, (int)nbpixels*2/3);
    
    for (int i = 0; i < network.nb_layers; i++)
    {
	for (int j = 0; j<network.layers[i].nb_cells; j++)
	{
	    network.layers[i].cells[j].biais = my_rand();
	    for (int k = 0; k < network.layers[i].cells[j].nb_weights; k++)
	    {
		network.layers[i].cells[j].weights[k] = my_rand();
	    }
	}
    }

    return network;
}

Neural_Network xorInitialisation()
{
    Neural_Network network;
    network.nb_layers = 2;
    network.layers[0] = Create_Layer(2, 2);
    network.layers[1] = Create_Layer(1, 2);
    network.output = 0.0;

    for(int i = 0; i < network.nb_layers; i++)
    {
        for(int j = 0; j < network.layers[i].nb_cells; j++)
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


Neural_Network ForwardPass(double entries[], Neural_Network network)
{
    //Le passage de Xor à OCR est similaire pour le traitement du premier layer.
    Neural_Network_Layer layer, previous_layer;

    // First Layer treatment
    layer = network.layers[0];
    for(int i = 0; i < layer.nb_cells; i++)
    {
        Neural_Network_Cell cell = layer.cells[i];
        double tmp = cell.biais;
        for (int j = 0; j < cell.nb_weight; j++)
        {
            tmp += cell.weights[j] * entries[j];
        }
        network.layers[0].cells[i].output = sigmoid(tmp);
    }
	
    //Cette fois, on a plus qu'un noeud en output, donc plus de network.output en int,
    //mais on peut mettre un char à la place pour accéder au résultat renvoyé par notre réseau.
    // Output Layer treatment
    // TO-DO : adapter cette partie du traitement.
    layer = network.layers[1];
    previous_layer = network.layers[0];
    Neural_Network_Cell cell = layer.cells[0];
    double tmp = cell.biais;
    for (int k = 0; k < cell.nb_weight; k++)
    {
        tmp += cell.weights[k]*previous_layer.cells[k].output;
    }
    network.layers[1].cells[0].output = sigmoid(tmp);
    
    //On récupère l'indice de la valeur d'output la plus grande
    //après le traitement.
    int indicemax = getIndiceMax(network)
    network.output = indiceToChar(indicemax);

    return network;
}

Neural_Network BackwardPass(double expected[], double entries[][2], 
                                            Neural_Network network, int i_data)
{
    double cell_output = network.layers[1].cells[0].output;
    double dCell_output = cell_output*(1-cell_output);
    double dError = (expected[i_data]-cell_output);
    
    for (int j = 0; j < network.layers[0].cells[0].nb_weight; j++)
    {
        double f = network.layers[0].cells[j].output;
        network.layers[1].cells[0].previous_dError[j] = dCell_output * dError;
        network.layers[1].cells[0].weights[j] += f * dCell_output * dError;
    }
    
    network.layers[1].cells[0].biais += dCell_output * dError;

    for (int i = 0; i < network.layers[0].nb_cells; i++)
    {
        double cell_output = network.layers[0].cells[i].output;
        double dg = cell_output*(1-cell_output);
        double dError = network.layers[1].cells[0].previous_dError[i];
        
        for (int j = 0; j < network.layers[0].cells[i].nb_weight; j++)
        {
            double f = entries[i_data][j];
            dError *= network.layers[1].cells[0].weights[i];
            network.layers[0].cells[i].weights[j] += f * dg * dError;
        }
        network.layers[0].cells[i].biais += dg * dError;
    }

    return network;
}
