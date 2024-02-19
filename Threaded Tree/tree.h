#ifndef TREE_H
#define TREE_H

#include "file.h"

typedef enum Tag
{
	MAINLINK,
	THREAD
} Tag;

typedef struct Node 
{
	char *key;
	int info;
	struct Node *left;
	struct Node *right;
	Tag tag; 
} Node;

typedef struct Tree
{
	Node *root;
} Tree;

typedef enum Errors
{
	OK,
	KEY_NOT_FOUND,
	DUPLICATE_KEY,
	FILE_NOT_FOUND
} Errors;

Tree *new_tree();
Node *new_node(const char *, const int);

Errors tree_insert(Tree *, const char *, const int, int *);
Errors insert(Node *, const char *, const int, int *);

Errors tree_find(Tree *, const char *, Node **, int);
Errors find(Node *, const char *, Node **, Node **);
Errors s_find(Tree *, const char *, Node **);

Errors tree_import(Tree *, const char *);

Errors tree_delete(Tree *, const char *);

void tree_traversal(Tree *, const char *, int);

void tree_print(Node *, int);

void free_tree(Tree **);

void free_node(Node *);

int starts_with(const char *, const char *);

Node *max_difference(Tree *, const char *);
Node *get_max(Node *);
Node *get_min(Node *);

#endif
