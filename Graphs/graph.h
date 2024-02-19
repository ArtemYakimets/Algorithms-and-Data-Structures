#ifndef GRAPH_H
#define GRAPH_H

#include "stack.h"

typedef enum Errors
{	
	OK,
	VERTEX_NOT_FOUND,
	VERTEX_ALREADY_EXISTS,
	EDGE_NOT_FOUND,
	EDGE_ALREADY_EXISTS,
	NOT_NEIGHBORING
} Errors;
/*
typedef enum Type
{
	START,
	END,
	ORDINARY
} Type;

typedef struct Vertex
{
	int x;
	int y;
	Type type;
} Vertex;

typedef struct Node 
{
	Vertex *vertex;
	struct Node *next;
} Node;

typedef struct List 
{
	Vertex *vertex;
	Node *head;
	struct List *next;
}  List;

typedef struct Graph
{
	List *head;
} Graph;
*/
Graph *new_graph();
Vertex *new_vertex(const int, const int, Type);
Node *new_node(Vertex *);
List *new_list(const int, const int, Type);

Errors graph_find_vertex(Graph *, const int, const int, List **, List **);

Errors graph_find_edge(Graph *, const int, const int, const int, const int, Vertex **, Vertex **);

Errors find_edge(List *, const int, const int, Node **, Node**);

Errors graph_new_edge(Graph *, const int, const int, const int, const int);

Errors graph_new_vertex(Graph *, const int, const int, Type);

Errors graph_delete_edge(Graph *, const int, const int, const int, const int);

Errors graph_delete_vertex(Graph *, const int, const int);

Errors graph_change_vertex(Graph *, const int, const int, Type);

Errors depth_first_search(Graph *, const int, const int);

void dfs(Graph *, List *, Vertex *, Stack *);

void graph_print(const Graph *);

void free_list(List **);

void free_graph(Graph **);

#endif
