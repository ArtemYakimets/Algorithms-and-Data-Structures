#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "io.h"

int line_insert(Line *l)
{
	printf("Enter the size of the line\n");
	if (scan(&l->size, 1))
		return 1;
	printf("Enter the elements\n");
	l->data = (int *) calloc(l->size, sizeof(int));
	for (int i = 0; i < l->size; ++i)
		if (scan(&l->data[i], 0))
		{
			free(l->data);
			return 2;
		}
	return 0;
}

void line_print(Line l)
{
	for (int i = 0; i < l.size; ++i)
		printf("%d ", l.data[i]);
}
