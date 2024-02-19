#include <stdio.h>
//#include <stdlib.h>

//#include "line.h"
#include "matrix.h"

int main()
{
	Matrix *x = matrix_new();
	x = matrix_insert(x);
	if (x == NULL)
		return 1;
	printf("Before sort\n");
	matrix_print(x);
	x = matrix_sort(x);
	//qsort(x->data, x->size, sizeof(Line), (int (*)(const void *, const void *)) cmp);
	printf("After sort\n");
	matrix_print(x);
	matrix_free(x);
	return 0;
}
