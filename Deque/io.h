//#ifdef VECTOR_C
//#include "vector.h"
//#elif defined(LIST_C)
//#include "list.h"
//#endif

#ifndef IO_H
#define IO_H

#include "patient.h"

int insert(Patient **, int *);
int check_int(int, int);
int check_slashes(const char *, int);

#endif
