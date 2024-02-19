#ifndef RUN_H
#define RUN_H

#include "patient.h"

#ifdef VECTOR_C
#include "vector.h"
#elif defined(LIST_C)
#include "list.h"
#endif

int deque_run(Patient **, int *, Deque *);

#endif
