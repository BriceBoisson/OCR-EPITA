#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct
{
    int nb_weight;
    double weights[100];
    double previous_dError[10];
    double biais;
    double output;
} Neural_Network_Cell;

typedef struct
{
    int nb_cells;
    Neural_Network_Cell cells[100];
} Neural_Network_Layer;


typedef struct
{
    int nb_layers;
    Neural_Network_Layer layers[10];
    double output;
} Neural_Network;

Neural_Network_Cell Create_Cell(int nb_weight);
Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight);

#endif
