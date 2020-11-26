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

char generateChar(void)
{
    char alph[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int len = strlen(alph);
    return alph[rand()%len];
}

int charToIndice(char c)
{
    int asciic = (int)c;
    if (asciic>48 && asciic<58)
	return(asciic - 48);
    if (asciic>64 && asciic<91)
	return(asciic - (64-10);
    if (ascii>96 && asciic<123)
	return(asciic - (96 - 26 -10));
    return (62);
}

char indiceToChar(int indice);
//TO-DO : écrire donction indiceToChar, inverse de celle du dessus.

double* imagetomatrix(char* str);
//TO-DO : écrire fonction image to matrix
