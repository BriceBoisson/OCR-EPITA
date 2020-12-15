#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct
{
    int nb_weight;
    double *weights;
    double *previous_dError;
    double biais;
    double output;
} Neural_Network_Cell;

typedef struct
{
    int nb_cells;
    Neural_Network_Cell *cells;
} Neural_Network_Layer;


typedef struct
{
    int nboutput;
    int nb_layers;
    Neural_Network_Layer *layers;
    double output;
} Neural_Network;

Neural_Network_Cell Create_Cell(int nb_weight);
Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight);

void Free_Network(Neural_Network *network);

int getIndiceMax(Neural_Network *network);
int Save_Network(Neural_Network *network, char* filename);
int Load_Network(Neural_Network *network, char* filename);

#endif
