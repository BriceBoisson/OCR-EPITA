# include <stdio.h>
# include "segmentation.h"
# include "extraction.h"


int create_m(size_t x, size_t y)
// this function create the list of matrix letters
{
    struct matrix *m = calloc(sizeof(int));
    m -> row = x;
    m -> col = y;
    m -> p = calloc(sizeof(struct matrix) * x * y);
    // initialize the list m with just 0
    // its size is equal to total pixels in img (cf segmentation.c)

    return m;
}

struct matrix* separate(struct matrix *m, size_t bl, size_t el,size_t bc,size_t ec)
// 
{
    struct matrix *matrix = create_m(x, y);
    size_t x = el - bl;
    size_t y = ec - bc;
    size_t c = m -> col;
    size_t cm = matrix -> col;

    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            matrix -> p[i * cm + j] = m -> p[(i + bl) * c + j + bc];
        }
    }

    return matrix;
}

void free_matrix(struct matrix *m)
// free the matrix
{
    free(m -> p);
    free(m);
}
