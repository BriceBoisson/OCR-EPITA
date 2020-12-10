#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

#include <SDL2/SDL_image.h>

#include "traitement.h"
#include "toolsnetworks.h"
#include "training.h"
#include "structure.h"
#include "Load.h"


// Definition des fonctions de type outils et fonctions mathématiques

float my_rand(void)
{
    return ((float)(rand() % 10000)/5000) - 1;
}

double sigmoid(double val)
{
    return (1.0 / (1.0 + exp(-1.0 * val)));
}

void softmax(Neural_Network_Layer *layer){
    double min = 0;
    for (int i = 0; i < layer->nb_cells; i++)
    {
        if (layer->cells[i].output < min){
            min = layer->cells[i].output;
        }
    }

    //printf("%f", min);
    double somme = 0;
    for (int i = 0; i < layer->nb_cells; i++)
    {
        layer->cells[i].output -= min;
        somme += exp(layer->cells[i].output);
        //printf("%f  %f\n",layer->cells[i].output , exp(layer->cells[i].output));
    }
    
    //printf("somme %f\n", somme);
    for (int i = 0; i < layer->nb_cells; i++){
        layer->cells[i].output = (exp(layer->cells[i].output)/somme);
    }
}

int charToIndice(char c)
{
    int asciic = (int)c;
    if (asciic>48 && asciic<58)
	return(asciic - 48);
    if (asciic>64 && asciic<91)
	return(asciic - (64-10));
    if (asciic>96 && asciic<123)
	return(asciic - (96 - 26 -10));
    return (62);
}

char indiceToChar(int indice){
    if (indice < 26){
        return indice + 97;
    }
    else if (indice < 52)
    {
        return indice + 39;
    }
    else
    {
        return indice - 4;
    }
}

double* imagetomatrix(char* str, int size){
    SDL_Surface *loadedImage = 0;
    loadedImage = SDL_LoadBMP(str);
    //loadedImage = IMG_Load(str);
    double *img = NULL;

    if (!loadedImage)
    {
        printf("Can't find the bmp file, %s\n", str);
        return img;
    }

    img = resizechar(loadedImage, size);

    //SDL_FreeSurface(loadedImage);
    return img;
}

double *segmentationtomatrix(SDL_Surface *loadedImage, int size){
    double *img = NULL;

    if (!loadedImage)
    {
        printf("Can't find the bmp file\n");
        return img;
    }

    img = resizechar(loadedImage, size);

    //SDL_FreeSurface(loadedImage);
    return img;
}

double generateChar(){
    return ((double) (rand()%62));
}

