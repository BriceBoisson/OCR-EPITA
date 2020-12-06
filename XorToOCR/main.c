#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"


int main(void)
{
    srand(time(NULL));

    Neural_Network network = Initialisation();
    //imagetomatrix("image.bmp", 20);

    for (int i = 0; i < 1; i++){
        for (int j = 0; j < network.layers[i].nb_cells; j++){
            //printf("%d\n", network.layers[i].nb_cells);
            printf("biais-%d-%d : %f\n", i, j, network.layers[i].cells[j].biais);
            for (int k = 0; k < network.layers[i].cells[j].nb_weight; k++)
            {
                printf("poid-%d-%d-%d : %f\n", i, j, k, network.layers[i].cells[j].weights[k]);
            }
            
        }
    }

    Save_Network(&network);

    //training(&network, 100);

    //XOR(network);

    return 0;
}
