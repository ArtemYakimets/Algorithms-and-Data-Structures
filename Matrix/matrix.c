#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "line.h"
#include "io.h"

Matrix *matrix_new() {
	return (Matrix *) calloc(1, sizeof(Matrix)); 
}

Matrix *matrix_insert(Matrix *x) 
{
	printf("Enter the number of lines\n");
	if (scan(&x->size, 1))
	{
		free(x);
		return NULL;
	}
	
	x->data = (Line *) calloc(x->size, sizeof(Line));	
	for (int i = 0; i < x->size; ++i)
	{
		int status = line_insert(x->data+i);
		if (status == 1)
		{
			free(x->data);
			free(x);
			return NULL;
		}
		else if (status == 2)
		{
			free(x->data);
			free(x);
			return NULL;
		}	
	}
	return x;	
}

void matrix_print(Matrix *x)
{
	for (int i = 0; i < x->size; ++i)
	{
		line_print(x->data[i]);
		printf("\n");
	}
}

int cmp(const Line *l1, const Line *l2)
{
	return l1->data[0] - l2->data[0];
}

void matrix_free(Matrix *x)
{
	for (int i = 0; i < x->size; ++i)
		free(x->data[i].data);
	free(x->data);
	x->size = 0;
	x->data = NULL;
	free(x);
}

Matrix *matrix_sort(Matrix *x)
{
	qsort(x->data, x->size, sizeof(Line), (int(*)(const void *, const void *)) cmp);
	return x;
}
