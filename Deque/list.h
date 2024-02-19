#ifndef LIST_H
#define LIST_H

#include "patient.h"

typedef struct Node {
	Patient patient;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Deque {
	int size;
	Node *head;
	Node *tail;
} Deque;

Deque *new_deque(int);
void deque_delete(Deque **);
int push_front(Deque *, Patient );
int pop_front(Deque *, Patient *);
int push_back(Deque *, Patient );
int pop_back(Deque *, Patient *);
void deque_print(const Deque *);
Node *get_element (Deque *, int);
int deque_run(Patient **, int *len, Deque *);

#endif
