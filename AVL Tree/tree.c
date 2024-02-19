#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Tree *new_tree()
{
	Tree *tree = (Tree *) calloc (1, sizeof(tree));
	tree->root = NULL;
	return tree;
}

Item *new_item(const char *info)
{
	Item *new = (Item *) calloc (1, sizeof(Item));
	new->info = strdup(info);
	new->release = 1;
	return new;
}

Node *new_node(const int key, const char *info)
{
	Node *node = (Node *) calloc(1, sizeof(Node));
	node->key = key;
	node->head = new_item(info);
	node->height = 0;
	return node;
}


int get_height(Node *node)
{
	if (node == NULL)
		return -1;
	else 
		return node->height;
}

void update_height(Node *node)
{
	if (get_height(node->right) > get_height(node->left))
		node->height = get_height(node->right) + 1;
	else
		node->height = get_height(node->left) + 1;
}

int get_balance(Node *node)
{
	int balance;
	
	if (node == NULL)
		return 0;
	else
	{
		balance = get_height(node->right) - get_height(node->left);
		return balance;
	}
	// если минус, то влево	
}

void swap(Node *a, Node *b)
{
	int tmp_key = a->key;
	a->key = b->key;
	b->key = tmp_key;

	Item *tmp_head = a->head;
	a->head = b->head;
	b->head = tmp_head;
}

void rotate_right(Node *node)
{
	swap(node, node->left);
	
	Node *tmp = node->right;
	node->right = node->left;
	node->left = node->right->left;
	node->right->left = node->right->right;
	node->right->right = tmp;
			
	update_height(node->right);
	update_height(node);
}

void rotate_left(Node *node)
{
	swap(node, node->right);

	Node *tmp = node->left;
	node->left = node->right;
	node->right = node->left->right;
	//node->right->left = node->right->right;
	node->left->right = node->left->left;
	node->left->left = tmp;
		
	update_height(node->left);
	update_height(node);
}

void balance(Node *node)
{
	update_height(node);
	if (get_balance(node) == 2)
	{
		if (get_balance(node->right) < 0)
			rotate_right(node->right);
		rotate_left(node);
		return;
	}

	if (get_balance(node) == -2)
	{
		if (get_balance(node->left) > 0)
			rotate_left(node->left);
		rotate_right(node);
		return;
	}
}

Errors tree_insert(Tree *tree, const int key, const char *info)
{
	if (tree->root == NULL)
	{
		tree->root = new_node(key, info);
		return OK;
	}

	if (insert(tree->root, key, info) == OK)
		return OK;
}

Errors insert(Node *node, const int key, const char *info)
{
	
	if (key < node->key)
	{
		if (node->left == NULL)
			node->left = new_node(key, info);
		else
			insert(node->left, key, info);
	}
	else if (key > node->key)
	{
		if (node->right == NULL)
			node->right = new_node(key, info);
		else
			insert(node->right, key, info);
	}
	else
	{
		Item *new = new_item(info);
		new->release = node->head->release + 1;
		new->next = node->head;
		node->head = new;
	}
	balance(node);
	return OK;
}

Errors tree_find(Tree *tree, const int key, const int release, Node **node, Item **found, int opt)
{
	if (opt == 0)
	{
		if (find(tree->root, key, node) == KEY_NOT_FOUND)
			return KEY_NOT_FOUND;

		Item *p = (*node)->head;
		while (p != NULL)
		{
			if (p->release == release)
			{
				*found = p;
				return OK;
			}
			p = p->next;
		}
		if (p == NULL)
			return KEY_NOT_FOUND;
	}	
	else
	{
		if (s_find(tree->root, key, node) == KEY_NOT_FOUND)
			return KEY_NOT_FOUND;
	}

	return OK;
}

Errors find(Node *node, const int key, Node **found)
{
	if (node == NULL)
		return KEY_NOT_FOUND;

	if (node->key == key)
	{
		*found = node;
		return OK;
	}

	if (key < node->key)
		find(node->left, key, found);
	else 
		find(node->right, key, found);
}

Errors s_find(Node *node, const int key, Node **found)
{	
	if (key < node->key)
		return KEY_NOT_FOUND;
	if ((key >= node->key) && node->right == NULL)
	{
		*found = node;
		return OK;
	}
	else if ((key >= node->key) && (key < node->right->key))
	{
		*found = node;
		return OK;
	}
	else 
		s_find(node->right, key, found);
}

Errors tree_delete(Tree *tree, const int key, const int release)
{
	Node *node = tree->root;
	Node *par = NULL;		

	if (node->key != key)
	{
		if (delete(tree->root, par, key, release) == KEY_NOT_FOUND)
			return KEY_NOT_FOUND;
	}
	else 
	{
		Item *p = node->head;
		Item *prev = NULL;
		while (p != NULL)
		{
			if ((prev != NULL) && (p->release == release))
			{
				prev->next = p->next;
				Item *del = p;
				free(del->info);
				free(del);
				break;
			}
			else if ((prev == NULL) && (p->release == release))
			{
				node->head = p->next;
				Item *del = p;
				free(del->info);
				free(del);
				break;
			}
			else
			{
				prev = p;
				p = p->next;
			}
		}
		if (p == NULL)
			return KEY_NOT_FOUND;

		if (node->head == NULL)
		{
			if (node->right == NULL)
				tree->root = node->left;
			else
			{
				Node *right = node->right;
				if (right->left == NULL)
				{
					right->left = node->left;
					tree->root = right;
				}
				else 
				{
					Node *succ = right->left;
					while (succ->left != NULL)
					{
						right = succ;
						succ = succ->left;
					}
					right->left = succ->right;
					succ->left = node->left;
					succ->right = node->right;
					tree->root = succ;
				}
			}
			free(node);
		}
	}
	return OK;
}

Errors delete(Node *node, Node *par, const int key, const int release)
{
	if (node == NULL)
		return KEY_NOT_FOUND;
	
	if (key < node->key)
	{
		par = node;
		return delete(node->left, par, key, release);
	}
	else if (key > node->key)
	{
		par = node;
		return delete(node->right, par, key, release);
	}
	else
	{
		Item *p = node->head;
		Item *prev = NULL;
		while (p != NULL)
		{
			if ((prev != NULL) && (p->release == release))
			{
				prev->next = p->next;
				Item *del = p;
				free(del->info);
				free(del);
				break;
			}
			else if ((prev == NULL) && (p->release == release))
			{
				node->head = p->next;
				Item *del = p;
				free(del->info);
				free(del);
				break;
			}
			else
			{
				prev = p;
				p = p->next;
			}
		}
		if (p == NULL)
			return KEY_NOT_FOUND;

		if (node->head == NULL)
		{
			if ((node->left == NULL) && (node->right == NULL))
				if (node == par->left)
					par->left = NULL;
				else 
					par->right = NULL;	
			else if (node->left == NULL)
			{
				if (node == par->left)
					par->left = node->right;
				else 
					par->right = node->right;
			}
			else if (node->right == NULL)
			{
				if (node == par->left)
					par->left = node->left;
				else
					par->right = node->left;
			}
			else 
			{
				Node *right = node->right;
				if (right->left == NULL)
				{
					right->left = node->left;
					if (node == par->left)
						par->left = right;
					else
						par->right = right;
				}
				else
				{
					Node *succ = right->left;
					while (succ->left != NULL)
					{
						right = succ;
						succ = succ->left;
					}
					right->left = succ->right;
					succ->left = node->left;
					succ->right = node->right;
					if (node == par->left)
						par->left = succ;
					else
						par->right = succ;
				}
			}
			free(node);
		}	
	}
	balance(par);
	return OK;
}

void tree_traversal(Node *node)
{
	if (node != NULL)
	{
		tree_traversal(node->left);
		Item *p = node->head;
		while (p != NULL)
		{
			printf("key: %d\n", node->key);
			printf("release: %d\n", p->release);
			printf("info: %s\n\n", p->info);
			p = p->next;
		}
		tree_traversal(node->right);
	}
}
Errors tree_import(Tree *tree, const char *name)
{
	FILE *file = fopen(name, "r");

	if (file == NULL)
		return FILE_NOT_FOUND;

	char *key;
	char *info;
	int ins;

	for(;;)
	{
		key = freadline(file);
		if (key == NULL)
			break;

		info = freadline(file);
		if (info == NULL)
		{
			free(key);
			break;
		}

		int k = atoi(key);

		ins = tree_insert(tree, k, info);
		if (ins != OK)
		{
			free(key);
			free(info);
			fclose(file);
			return (ins);
		}
		free(key);
		free(info);
	}
	fclose(file);
	return OK;
}

void tree_print(Node *node, int space)
{
	if (node == NULL)
		return;

	space += 4;

	tree_print(node->right, space);

	printf("\n");
	for (int i = 4; i < space; i++)
		printf(" ");
	printf("%d\n", node->key);

	tree_print(node->left, space);
}

void free_tree(Tree **tree)
{
	free_node((*tree)->root);
	free(*tree);
}

void free_node(Node *node)
{
	if (node == NULL)
		return;

	free_node(node->left);
	free_node(node->right);

	Item *p = node->head;
	Item *prev = p;
	while (p != NULL)
	{
		p = p->next;
		free(prev->info);
		free(prev);
		prev = p;
	}
	free(node);
}

