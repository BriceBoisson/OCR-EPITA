#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "traitement.h"
#include "tools.h"
#include "training.h"
#include "structure.h"

// Definition des structure du reseau de neurone

Neural_Network_Cell Create_Cell(int nb_weight)
{
    Neural_Network_Cell cell;
    cell.nb_weight = nb_weight;
    cell.biais = 0;
    cell.output = 0;
    for (int i = 0; i < nb_weight; i++)
    {
        cell.weights[i] = 0.0;
        cell.previous_dError[i] = 0.0;
    }
    return cell;
}


Neural_Network_Layer Create_Layer(int nb_cell, int nb_weight)
{
    Neural_Network_Layer layer;
    layer.nb_cells = nb_cell;
    for (int i = 0; i < nb_cell; i++)
    {
        layer.cells[i] = Create_Cell(nb_weight);
    }
    return layer;
}

