#ifndef DIALOG_H
#define DIALOG_H

#include "graph.h"

int dialog(const char **, int);

int add_vertex(Graph *);
int add_edge(Graph *);
int edge_find(Graph *);
int vertex_find(Graph *);
int delete_edge(Graph *);
int delete_vertex(Graph *);
int change_vertex(Graph *);
int traversal(Graph *);
int print_graph(Graph *);
char *get_type(Type);
int get_int(int *);
int get_char(char *);

#endif
