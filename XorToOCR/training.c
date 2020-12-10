#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"

#define NB_OUTPUT 7

void training(Neural_Network *network, int nb_repetition)
{
	int nbchar = 7;
	int nbimageschar = 53;
	int datasetsize = nbchar * nbimageschar;
    printf("Waiting for training\n");

    //On construit les tableaux input de taille nbrepetition, et on initialise
    //en même temps le coût attendu à 0 pour toutres les répétitions (on a nbrépétition
    //tableaux de taille 63 initialisés à 0).
    double **input = (double**)malloc(datasetsize*sizeof(double*));
    double **cost = (double**)malloc(datasetsize*sizeof(double));

	char str[100];

	for (int i = 0; i < datasetsize; i++)
	{
		cost[i] = (double*)calloc(NB_OUTPUT, sizeof(double));
	}
	
	for (int i = 0; i < nbimageschar; i++){
		for (int j = 0; j < nbchar; j++){
			sprintf(str, "image-%d-%d.bmp", j, i+1);
			input[i*nbchar+j] = imagetomatrix(str, 20);
			cost[i*nbchar+j][j] = 1;
		}
	}

	/*input[0] = imagetomatrix("image-0-1.bmp", 20);
	cost[0][0] = 1;
	input[1] = imagetomatrix("image-0-2.bmp", 20);
	cost[1][0] = 1;
	input[2] = imagetomatrix("image-0-3.bmp", 20);
	cost[2][0] = 1;
	input[3] = imagetomatrix("image-0-4.bmp", 20);
	cost[3][0] = 1;
	//input[4] = imagetomatrix("image-0-5.bmp", 20);
	//cost[4][0] = 1;
	double *sortie1 = imagetomatrix("image-0-5.bmp", 20);
	double *sortie2 = imagetomatrix("image-1-5.bmp", 20);
	input[5] = imagetomatrix("image-1-1.bmp", 20);
	cost[5][1] = 1;
	input[6] = imagetomatrix("image-1-2.bmp", 20);
	cost[6][1] = 1;
	input[7] = imagetomatrix("image-1-3.bmp", 20);
	cost[7][1] = 1;
	input[4] = imagetomatrix("image-1-4.bmp", 20);
	cost[4][1] = 1;
	//input[9] = imagetomatrix("image-1-5.bmp", 20);*/
	//cost[9][1] = 1;

	//double *i = input[0];

	/*for (int k = 0; k < 20; k++)
    {
        for (int z = 0; z < 20; z++)
        {
           printf("%d ", (int) i[z*20 + k]);
        }
        printf("\n");
    }*/

	/*for (int i = 0; i < nbimageschar; i++){
		int r = rand()%54+1;

		//On génère un caractère aléatoire entre 0 et 61, qui est un chiffre, une majuscule ou une minuscule.
		char c = generateChar();

		//Chaque output de sortie correspond à un caractère précis, on récupère avec cette
		//fonction l'indice correspondant au caractère c.
		//Avec cet indice, on met à jour la valeur de cost correspondante.
		if (c == 0){
			cost[i*3] = 0;
		}
		else if (c == 5)
		{
			cost[i*3] = 1;
		}
		else
		{
			cost[i*3] = 2;
		}

		//En utilisant le nombre aléatoire produit tout à l'heure et notre caractère, on
		//récupère une image dans notre dataset qui représente ce caractère, de police numéro r.
		//Avec la fonction imagetomatrix, on transforme les pixels de l'image en une matrice
		//unidimensionnelle, que l'on stocke en input[i].
		input[i*3] = imagetomatrix(strcat(strcat(strcat("image-", c),strcat("-", r)), ".bmp"));

		cost[i*3+1] = 0;
		input[i*3+1] = imagetomatrix(strcat(strcat("image-0",strcat("-", i)), ".bmp"));

		cost[i*3+2] = 1;
		input[i*3+2] = imagetomatrix(strcat(strcat("image-5",strcat("-", i)), ".bmp"));
	}*/
	double err = 1.0;
	while (err > 0.10)
	{
		Free_Network(network);
		*network = Initialisation();
		for (int i=0; i<30; i++)
		{
			err = 0.0;
			for (int j = 0; j < datasetsize; j++){
				//On fait ensuite appel au ForwardPass sur cette itération <=> on voit ce que renvoie
				//notre réseau pour la matrice de pixel correspondant à l'image récupérée.
				ForwardPass(input[j], network);

				double tmp_err = 0.0;
				for (int k = 0; k < NB_OUTPUT; k++)
				{
					tmp_err += (cost[j][k] - network->layers[1].cells[k].output) * (cost[j][k] - network->layers[1].cells[k].output);
				}

				if (err != err){break;}


				tmp_err /= NB_OUTPUT;
				err += tmp_err;

				BackwardPass(cost[j], input[j], network);
			}

			err /= datasetsize;
			printf("Erreur : %f\n", err);
		}
	}

	if (err != err){
		for (int i = 0; i < 1; i++){
        for (int j = 0; j < network->layers[i].nb_cells; j++){
            //printf("%d\n", network.layers[i].nb_cells);
            printf("biais-%d-%d : %f\n", i, j, network->layers[i].cells[j].biais);
            for (int k = 0; k < network->layers[i].cells[j].nb_weight; k++)
            {
                printf("poid-%d-%d-%d : %f\n", i, j, k, network->layers[i].cells[j].weights[k]);
            }
            
        }
    }
	}
	
else{
    for (int i=0; i<nb_repetition; i++)
    {

		for (int j = 0; j < datasetsize; j++){
			//On fait ensuite appel au ForwardPass sur cette itération <=> on voit ce que renvoie
			//notre réseau pour la matrice de pixel correspondant à l'image récupérée.
			ForwardPass(input[j], network);

			double tmp_err = 0.0;
			for (int k = 0; k < NB_OUTPUT; k++)
			{
				tmp_err += (cost[j][k] - network->layers[1].cells[k].output) * (cost[j][k] - network->layers[1].cells[k].output);
			}

			tmp_err /= NB_OUTPUT;
			err += tmp_err;

			BackwardPass(cost[j], input[j], network);
		}

		err /= datasetsize;
		printf("Erreur : %f\n", err);
	}}

	double **inputtry = (double**)malloc(1*sizeof(double*));

	inputtry[0] = imagetomatrix("image1.bmp", 20);

	ForwardPass(inputtry[0], network);
	printf("%f", network->output);

	for (int i = 0; i < 1; i++){
		free(inputtry[i]);
	}
	
	free(inputtry);

	for (int i = 0; i < datasetsize; i++){
		free(input[i]);
	}
	for (int i = 0; i < NB_OUTPUT; i++)
	{
		free(cost[i]);
	}
	
	free(input);
	free(cost);

}
