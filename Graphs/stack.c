#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
Stack *new_stack()
{
	Stack *new = (Stack *) calloc(1, sizeof(Stack));
	return new;
}

int stack_push(Stack *s, Vertex *vertex)
{
	StackNode *new = (StackNode *) calloc(1, sizeof(StackNode));
	new->vertex = vertex;
	new->next = s->top;
	s->top = new;
	return 0;
}

int stack_pop(Stack *s)
{
	if (s->top == NULL)
		return 1;

	StackNode *p = s->top;
	s->top = p->next;
	free(p);
}

int visited(Stack *s, Vertex *v)
{
	StackNode *p = s->top;
	while(p != NULL)
	{
		if (p->vertex == v)
			return 1;
		p = p->next;		
	}	
	return 0;
}

void free_stack(Stack **s)
{
	StackNode *p = (*s)->top;
	StackNode *next = NULL;
	while(p != NULL)
	{
		next = p->next;
		free(p);
		p = next;
	}
	free(*s);
}

void print_stack(const Stack *s)
{
	printf("\n   END\n\n");
	StackNode *p = s->top;
	while(p != NULL)
	{
		vertex_print(p->vertex);
		printf("\n   /\\\n\n");
		p = p->next;
	}
	printf("  START\n\n");
}

char get_t(Type t)
{
	char type;
	if (t == START)
		type = 's';
	else if (t == END)
		type = 'e';
	else
		type = 'o';
	return type;
}

void vertex_print(Vertex *v)
{
	char type = get_t(v->type);
	printf("(%d, %d, %c)\n", v->x, v->y, type);
}
