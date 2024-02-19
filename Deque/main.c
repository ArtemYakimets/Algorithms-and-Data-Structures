#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "run.h"

#define SIZE 5

#ifdef VECTOR_C
#include "vector.h"
#elif defined(LIST_C)
#include "list.h"
#endif


int main()
{
	int status;
	Patient *pts = NULL;
	int len = 0;
	status = insert(&pts, &len);
	if (status == 1)
		return 1;
	
	Deque *deque = new_deque(SIZE);
	status = deque_run(&pts, &len, deque);
	if (status == 1)
		return 1;
	deque_delete(&deque);
	return 0;
}

