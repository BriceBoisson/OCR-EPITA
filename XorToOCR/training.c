#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"

void training(Neural_Network *network, int nb_repetition)
{
	int nbchar = 3;
	int nbimageschar = 10;
	int datasetsize = nbchar * nbimageschar;
    printf("Waiting for training\n");

    //On construit les tableaux input de taille nbrepetition, et on initialise
    //en même temps le coût attendu à 0 pour toutres les répétitions (on a nbrépétition
    //tableaux de taille 63 initialisés à 0).
    double **input = (double**)malloc(datasetsize*sizeof(double*));
    double *cost = (double*)malloc(datasetsize*sizeof(double));

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

    for (int i=0; i<nb_repetition; i++)
    {
		double err = 0.0;

	for (int j = 0; j < datasetsize; j++){
		//On fait ensuite appel au ForwardPass sur cette itération <=> on voit ce que renvoie
		//notre réseau pour la matrice de pixel correspondant à l'image récupérée.
		ForwardPass(input[i], network);

		err += (cost[i] - network->output) * (cost[i] - network->output);

		BackwardPass(cost[j], input[j], network);
	}

    err /= datasetsize;
    printf("Erreur : %f\n", err);
	}
}
