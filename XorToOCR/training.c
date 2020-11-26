#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"

int nbimagesmax = 10;

Neural_Network training(Neural_Network network, int nbrepetition)
{
    printf("Waiting for training\n");

    //On construit les tableaux input de taille nbrepetition, et on initialise
    //en même temps le coût attendu à 0 pour toutres les répétitions (on a nbrépétition
    //tableaux de taille 63 initialisés à 0).
    double input[nbrepetition]["nombre de pixels de notre image"]
    double* cost[nbrepetition] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    double err = 1.0;
    for (int i=0; i<nbrepetition; i++)
    {
	int r = rand()%nbimagesmax;

	//On génère un caractère aléatoire, qui est un chiffre, une majuscule ou une minuscule.
	char c = generateChar();

	//Chaque output de sortie correspond à un caractère précis, on récupère avec cette
	//fonction l'indice correspondant au caractère c.
	int indicedec = charToIndice(c);

	//Avec cet indice, on met à jour la valeur de cost correspondante. 
	cost[i][indicedec]=1;

	//En utilisant le nombre aléatoire produit tout à l'heure et notre caractère, on
	//récupère une image dans notre dataset qui représente ce caractère, de police numéro r.
	//Avec la fonction imagetomatrix, on transforme les pixels de l'image en une matrice
	//unidimensionnelle, que l'on stocke en input[i].
	input[i] = imagetomatrix("image"+c+"-"+r+".png");
    	
	//On fait ensuite appel au ForwardPass sur cette itération <=> on voit ce que renvoie
	//notre réseau pour la matrice de pixel correspondant à l'image récupérée.
	network = ForwardPass(input[i], network);

	double error[network.nboutput];

	for (int j = 0; j<network.nboutput;j++)
	{
	    error[j]=(cost[i][j] - network.output[j]) * (cost[i][j] - network.output[j]);
	    err += error[j];
	}
	err /= network.nboutput;

	// On appelle le backward pass avec le tableau error, qui contient
        // l'erreur pour chaque neurone de sortie (c'est un tableau de taille 63

	//L'erreur est comme avant la somme des erreurs sur cette itération 
        //dentrainement, sauf quau lieu davoir 4 erreurs partielles dans une 
        //itération, on en a nboutput. On veut en effet que notre réseau saméliore
	//à chaque itération pour tous les calculs doutput, et pas seulement
        //pour le calcul de celui que lon attend.

        network = BackwardPass(cost[i], input[i], network);

    }
    
    printf("Erreur : %f\n", err);

    return network;
}

void XOR(Neural_Network network)
{
    double args[2] = {0.0, 0.0};
    int quit = 1;

    while(quit){
    	printf("XOR entries : ");
    	scanf("%lf %lf", &args[0], &args[1]);
    	network = ForwardPass(args, network);
    	printf("result : %f\n", network.output);
	printf("Press any key to continue or q to quit ");
	char q = 'a';
	scanf(" %c", &q);
	if (q == 'q'){
		quit = 0;
	}
    }
}

Neural_Network try(Neural_Network network)
{
    return network;
}
