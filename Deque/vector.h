#ifndef VECTOR_H
#define VECTOR_H

#include "patient.h"

typedef struct Deque{
	Patient *patient;
	int head;
	int tail;
	int size;
	int capacity;
} Deque;

Deque *new_deque(int);
void deque_delete(Deque **);
int push_front(Deque *, Patient );
int pop_front(Deque *, Patient *);
int push_back(Deque *, Patient );
int pop_back(Deque *, Patient *);
void deque_print(const Deque *);


#endif
