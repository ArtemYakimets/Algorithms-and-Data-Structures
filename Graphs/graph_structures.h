#ifndef GRAPH_STRUCTURES_H
#define GRAPH_STRUCTURES_H

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

#endif
