#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"



Neural_Network training()
{
    printf("Waiting for training\n");
    Neural_Network network;
    double b[4][2] = {{0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0}};
    double c[4] = {0.0,1.0,1.0,0.0};
    double err = 1.0;
    
    while (err > 0.01){
        network = Initialisation();
        for (int i = 0; i < 2000; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                network = ForwardPass(b[j], network);
                err += ((c[j] - network.output) * (c[j] - network.output));
                network = BackwardPass(c, b, network, j);
            }
            err /= 4;
        }
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
