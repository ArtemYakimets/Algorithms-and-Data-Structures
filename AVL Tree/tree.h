#ifndef TREE_H
#define TREE_H

#include "file.h"

typedef struct Item
{
	char *info;
	int release;
	struct Item *next;
} Item;

typedef struct Node 
{
	int key;
	Item *head;
	struct Node *left;
	struct Node *right;
	int height;
} Node;

typedef struct Tree
{
	Node *root;	
} Tree;

typedef enum Errors
{
	OK,
	KEY_NOT_FOUND,
	FILE_NOT_FOUND
} Errors;

Tree *new_tree();
Node *new_node(const int, const char *);
Item *new_item(const char *);

int get_height(Node *);
void update_height(Node *);
int get_balance(Node *node);
void swap(Node *, Node *);
void rotate_right(Node *);
void rotate_left(Node *);
void balance(Node *);

Errors tree_insert(Tree *, const int, const char *);
Errors insert(Node *, const int, const char *);

Errors tree_find(Tree *, const int, const int, Node **, Item **, int);
Errors find(Node *, const int, Node **);
Errors s_find(Node *, const int, Node **);

Errors tree_delete(Tree *, const int, const int);
Errors delete(Node *, Node *, const int, const int);

Errors tree_import(Tree *, const char *);

void free_tree(Tree **);
void free_node(Node *);

void tree_traversal(Node *node);
void tree_print(Node *, int);

#endif
