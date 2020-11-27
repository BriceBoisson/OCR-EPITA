#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"


// Definition des fonctions de type outils et fonctions mathématiques

float my_rand(void)
{
    return ((float)(rand() % 10000)/5000) - 1;
}

double sigmoid(double val)
{
    return (1.0 / (1.0 + exp(-1.0 * val)));
}
