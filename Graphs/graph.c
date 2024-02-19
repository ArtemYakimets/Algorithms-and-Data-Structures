#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

Graph *new_graph()
{
	Graph *new = (Graph *) calloc(1, sizeof(Graph));
	return new;
}

Vertex *new_vertex(const int x, const int y, Type type)
{
	Vertex *new = (Vertex *) calloc(1, sizeof(Vertex));
	new->x = x;
	new->y = y;
	new->type = type;
	return new;	
}

Node *new_node(Vertex *v)
{
	Node *new = (Node *) calloc(1, sizeof(Node));
	new->vertex = v;
	return new;	
}

List *new_list(const int x, const int y, Type type)
{
	List *new = (List *) calloc(1, sizeof(List));
	new->vertex = new_vertex(x, y, type);
	return new;
}

Errors graph_find_vertex(Graph *graph, const int x, const int y, List **found, List **prev)
{
	List *p = graph->head;
	while (p != NULL)
	{
		if ((p->vertex->x == x) && (p->vertex->y == y))
		{
			*found = p;
			return OK;
		}
		else
		{
			*prev = p;
			p = p->next;
		}
	}

	if (p == NULL)
		return VERTEX_NOT_FOUND;
}

Errors graph_find_edge(Graph *graph, const int x1, const int y1, const int x2, const int y2, Vertex **a, Vertex **b)
{
	List *l = NULL;
	List *prev_l = NULL;

	if (graph_find_vertex(graph, x1, y1, &l, &prev_l) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;	

	Node *n = NULL;
	Node *prev_n = NULL;
	if (find_edge(l, x2, y2, &n, &prev_n) == EDGE_NOT_FOUND)
		return EDGE_NOT_FOUND;

	*a = l->vertex;
	*b = n->vertex;
	return OK;
}

Errors find_edge(List *list, const int x, const int y, Node **found, Node **prev)
{
	Node *p = list->head;
	while (p != NULL)
	{
		if ((p->vertex->x == x) && (p->vertex->y == y))
		{
			*found = p;
			return OK;
		}
		else
		{
			*prev = p;
			p = p->next;
		}
	}	

	if (p == NULL)
		return EDGE_NOT_FOUND;
}

Errors graph_new_edge(Graph *graph, const int x1, const int y1, const int x2, const int y2)
{
	List *a = NULL;
	List *b = NULL;
	List *prev_a = NULL;
	List *prev_b = NULL;

	Node *ab = NULL;
	Node *ba = NULL;
	Node *prev_ab = NULL;
	Node *prev_ba = NULL;
	if (((abs(x2 - x1) == 1) && (abs(y2 - y1) == 0)) || ((abs(x2 - x1) == 0) && (abs(y2 - y1) == 1)))
	{
		if (graph_find_vertex(graph, x1, y1, &a, &prev_a) == VERTEX_NOT_FOUND)
			return VERTEX_NOT_FOUND;
			
		if (graph_find_vertex(graph, x2, y2, &b, &prev_b) == VERTEX_NOT_FOUND)
			return VERTEX_NOT_FOUND;

		if (find_edge(a, x2, y2, &ab, &prev_ab) == OK)
			return EDGE_ALREADY_EXISTS;

		if (find_edge(b, x1, y1, &ba, &prev_ba) == OK)
			return EDGE_ALREADY_EXISTS;

		if (a->head == NULL)
			a->head = new_node(b->vertex);
		else
		{
			Node *new1 = new_node(b->vertex);
			new1->next = a->head;
			a->head = new1;
		}

		if (b->head == NULL)
			b->head = new_node(a->vertex);
		else
		{
			Node *new2 = new_node(a->vertex);
			new2->next = b->head;
			b->head = new2;
		}
	}
	else 
		return NOT_NEIGHBORING;
	return OK;
}

Errors graph_new_vertex(Graph *graph, const int x, const int y, Type type)
{
	List *a = NULL;
	List *prev_a = NULL;
	if (graph_find_vertex(graph, x, y, &a, &prev_a) == OK)
		return VERTEX_ALREADY_EXISTS;

	if (graph->head == NULL)
		graph->head = new_list(x, y, type);
	else
	{
		List *new = new_list(x, y, type);
		new->next = graph->head;
		graph->head = new;
	}
	return OK;
}

Errors graph_delete_edge(Graph *graph, const int x1, const int y1, const int x2, const int y2)
{
	List *a = NULL;
	List *b = NULL;
	List *prev_a = NULL;
	List *prev_b = NULL;

	Node *ab = NULL;
	Node *ba = NULL;
	Node *prev_ab = NULL;
	Node *prev_ba = NULL;
	
	if (graph_find_vertex(graph, x1, y1, &a, &prev_a) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;

	if (graph_find_vertex(graph, x2, y2, &b, &prev_b) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;

	if (find_edge(a, x2, y2, &ab, &prev_ab) == EDGE_NOT_FOUND)
		return EDGE_NOT_FOUND;

	if (find_edge(b, x1, y1, &ba, &prev_ba) == EDGE_NOT_FOUND)
		return EDGE_NOT_FOUND;

	if (prev_ab == NULL)
		a->head = ab->next;
	else 
		prev_ab->next = ab->next;

	if (prev_ba == NULL)
		b->head = ba->next;
	else
		prev_ba->next = ba->next;

	free(ab);
	free(ba);
	return OK;
}

Errors graph_delete_vertex(Graph *graph, const int x, const int y)
{
	List *a = NULL;
	List *prev_a = NULL;

	if (graph_find_vertex(graph, x, y, &a, &prev_a) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;

	List *p = graph->head;
	while (p != NULL)
	{
		Node *ab = NULL;
		Node *prev_ab = NULL;
		if (find_edge(p, x, y, &ab, &prev_ab) == OK)
		{
			if (prev_ab == NULL)
				a->head = ab->next;
			else 
				prev_ab->next = ab->next;

			free(ab);
		}
		p = p->next;
	}

	if (prev_a == NULL)
		graph->head = a->next;
	else
		prev_a->next = a->next;

	free_list(&a);
	
	return OK;
}

Errors graph_change_vertex(Graph *graph, const int x, const int y, Type type)
{
	List *a = NULL;
	List *prev_a = NULL;

	if (graph_find_vertex(graph, x, y, &a, &prev_a) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;

	a->vertex->type = type;
	return OK;
}

Errors depth_first_search(Graph *graph, const int x, const int y)
{
	List *a = NULL;
	List *prev_a = NULL;

	if (graph_find_vertex(graph, x, y, &a, &prev_a) == VERTEX_NOT_FOUND)
		return VERTEX_NOT_FOUND;

	Vertex *v = a->vertex;
	Stack *path = new_stack();

	dfs(graph, a, v, path);
	free_stack(&path);
	return OK;
}

void dfs(Graph *graph, List *list, Vertex *curr, Stack *path)
{
	List *prev = NULL;
	stack_push(path, curr);

	if (curr->type == END)
	{
		printf("Path to end vertex:\n");
		print_stack(path);
		return;
	}

	Node *p = list->head;
	while (p != NULL)
	{
		Vertex *next_vertex = p->vertex;
		if (visited(path, next_vertex) == 0)
		{
			graph_find_vertex(graph, next_vertex->x, next_vertex->y, &list, &prev);
			dfs(graph, list, next_vertex, path);
		}
		p = p->next;
	}

	stack_pop(path);
}

void graph_print(const Graph *graph)
{
	char type;
	List *p = graph->head;
	while (p != NULL)
	{
		type = get_t(p->vertex->type);
		printf("(%d, %d, %c): ", p->vertex->x, p->vertex->y, type);
		Node *n = p->head;
		while (n != NULL)
		{
			type = get_t(n->vertex->type);
			printf("(%d, %d, %c) ", n->vertex->x, n->vertex->y, type);
			n = n->next;
		}
		printf("\n");
		p = p->next;
	}	
}

/*
void vertex_print(Vertex *v)
{
	char type = get_t(v->type);
	printf("(%d, %d, %c)", v->x, v->y, type);
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
*/

void free_list(List **list)
{
	free((*list)->vertex);
	Node *p = (*list)->head;
	Node *next = NULL;
	while (p != NULL)
	{
		next = p->next;
		free(p);
		p = next;
	}
	free(*list);
}

void free_graph(Graph **graph)
{
	List *p = (*graph)->head;
	List *next = NULL;
	while (p != NULL)
	{
		next = p->next;
		free_list(&p);
		p = next;
	}
	free(*graph);
}
