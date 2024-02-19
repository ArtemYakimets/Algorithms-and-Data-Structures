#ifndef MATRIX_H
#define MATRIX_H

#include "line.h"

typedef struct Matrix {
	int size;
	Line *data;
} Matrix;

void matrix_print(Matrix *);
Matrix *matrix_new();
Matrix *matrix_insert(Matrix *);
int cmp(const Line *, const Line *);
void matrix_free(Matrix *);
Matrix *matrix_sort(Matrix *);

#endif
