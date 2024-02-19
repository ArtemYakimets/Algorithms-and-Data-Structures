#ifndef STACK_H
#define STACK_H

#include "graph_structures.h"

typedef struct StackNode
{
	Vertex *vertex;
	struct StackNode *next;
} StackNode;

typedef struct Stack
{
	StackNode *top;
} Stack;

Stack *new_stack();
int stack_push(Stack *, Vertex *);
int stack_pop(Stack *);
void free_stack(Stack **);
void print_stack(const Stack *);
int visited(Stack *, Vertex *);
void vertex_print(Vertex *);
char get_t(Type);
#endif
