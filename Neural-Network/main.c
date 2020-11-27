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

    Neural_Network network = training();

    XOR(network);

    return 0;
}
