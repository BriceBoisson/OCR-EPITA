# ifndef EXTRACT_H
# define EXTRACT_H

struct matrix
{
    int row, col;
    int* p;
};

int create_list(size_t x, size_t y);
struct matrix* separate(struct matrix *m, size_t bl, size_t el,size_t bc,size_t ec);
void free_matrix(struct matrix *m);

# endif
