#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "traitement.h"
#include "toolsnetworks.h"
#include "training.h"
#include "structure.h"

#define NB_OUTPUT 65

void training(Neural_Network *network, int nb_repetition)
{
	int nbchar = 65;
	int nbimageschar = 53;
	int datasetsize = nbchar * nbimageschar;

    //On construit les tableaux input de taille nbrepetition, et on initialise
    //en même temps le coût attendu à 0 pour toutres les répétitions (on a
    //nbrépétition tableaux de taille 63 initialisés à 0).
    double **input = (double**)malloc(datasetsize*sizeof(double*));
    double **cost = (double**)malloc(datasetsize*sizeof(double));

	char str[100];

	for (int i = 0; i < datasetsize; i++)
	{
		cost[i] = (double*)calloc(NB_OUTPUT, sizeof(double));
	}
	
	for (int i = 0; i < nbimageschar; i++)
    {
		for (int j = 0; j < nbchar; j++)
        {
			sprintf(str, "src/Dataset/image-%d-%d.bmp", j, i+1);
			input[i * nbchar+j] = imagetomatrix(str, 20);
			cost[i * nbchar+j][j] = 1;
		}
	}

	double err = 1.0;

    for (int i = 0; i < nb_repetition; i++)
    {
		err = 0;
        
		for (int j = 0; j < datasetsize; j++)
        {
			//On fait ensuite appel au ForwardPass sur cette itération <=> on
            //voit ce que renvoie notre réseau pour la matrice de pixel
            //correspondant à l'image récupérée.
			ForwardPass(input[j], network);

			double tmp_err = 0.0;
            
			for (int k = 0; k < NB_OUTPUT; k++)
			{
				tmp_err += (cost[j][k] - network->layers[1].cells[k].output) * 
                            (cost[j][k] - network->layers[1].cells[k].output);
			}
            
			tmp_err /= NB_OUTPUT;
			err += tmp_err;

			BackwardPass(cost[j], input[j], network);
		}

		err /= datasetsize;
		printf("Erreur : %f\n", err);
	}

	for (int i = 0; i < datasetsize; i++)
    {
		free(input[i]);
	}
    
	for (int i = 0; i < datasetsize; i++)
	{
		free(cost[i]);
	}
	
	free(input);
	free(cost);
}
