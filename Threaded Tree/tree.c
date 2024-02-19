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

Node *new_node(const char *key, const int info)
{
	Node *node = (Node *) calloc(1, sizeof(Node));
	node->key = strdup(key);
	node->info = info;
	node->tag = THREAD;
	return node;
}

Errors tree_insert(Tree *tree, const char* key, const int info, int *old)
{
	if (tree->root == NULL)
	{
		tree->root = new_node(key, info);
		return OK;
	}

	if (insert(tree->root, key, info, old) == DUPLICATE_KEY)
		return DUPLICATE_KEY;
	
	return OK;	
}

Errors insert(Node *node, const char* key, const int info, int *old)
{		
	Node *tmp;
	if (strcmp(key, node->key) < 0)
	{
		if (node->tag == THREAD)
		{
			tmp = node->left;
			node->left = new_node(key, info);
			node->left->left = tmp;
			node->tag = MAINLINK;
		}
		else 
			if (insert(node->left, key, info, old) == DUPLICATE_KEY)
				return DUPLICATE_KEY;
	}
	else if (strcmp(key, node->key) > 0)
	{
		if (node->right == NULL)
		{
			node->right = new_node(key, info);
			node->right->left = node;
		}
		else
			if (insert(node->right, key, info, old) == DUPLICATE_KEY)
				return DUPLICATE_KEY;
	}
	else 
	{
		*old = node->info;
		node->info = info;
		return DUPLICATE_KEY;
	}
	return OK;
}

Errors tree_find(Tree *tree, const char *key, Node **found, int opt)
{
	Node *par = NULL;

	if (opt == 0) // обычный поиск
	{
		if (find(tree->root, key, &par, found) == KEY_NOT_FOUND)
			return KEY_NOT_FOUND;
	}
	else
	{
		if (s_find(tree, key, found) == KEY_NOT_FOUND)
			return KEY_NOT_FOUND;
	}

	return OK;
}

Errors s_find(Tree *tree, const char *key, Node **found)
{
	*found = max_difference(tree, key);
	if (*found == NULL)
		return KEY_NOT_FOUND;

	return OK;
}

Errors find(Node *node, const char *key, Node **par, Node **found)
{
	if (node == NULL)
		return KEY_NOT_FOUND;

	if (strcmp(node->key, key) == 0)
	{
		*found = node;
		return OK;
	}
	*par = node;

	if (strcmp(key, node->key) < 0 && node->tag == MAINLINK)
		find(node->left, key, par, found);
	else if (strcmp(key, node->key) > 0)
		find(node->right, key, par, found);
	else 
		return KEY_NOT_FOUND;
}

Node *get_max(Node *tmp)
{
	if (tmp == NULL)
		return NULL;

	while(tmp->right != NULL)
		tmp = tmp->right;

	return tmp;
}

Node *get_min(Node *tmp)
{
	if (tmp == NULL)
		return NULL;

	while (tmp->tag == MAINLINK)
		tmp = tmp->left;

	return tmp;
}

void tree_traversal(Tree *tree, const char *str, int opt)
{
	Node *node = tree->root;
	
	if (node == NULL)
		return;

	Node *tmp = get_max(node);

	while (tmp != NULL)
	{
		if (opt == 0) // обычный обход
		{
			printf("key: %s\n", tmp->key);
			printf("item: %d\n\n", tmp->info);
		}
		else // выводить только элементы, которые начинаются с заданной подстроки str
		{
			if (starts_with(tmp->key, str) == 1)
				{
					printf("key: %s\n", tmp->key);
					printf("item: %d\n\n", tmp->info);			
				}
		}

		if (tmp->tag == THREAD)
			tmp = tmp->left;
   		else
			tmp = get_max(tmp->left);	
	}
}


int starts_with(const char *str, const char *substr)
{
	int str_len = strlen(str);
	int substr_len = strlen(substr);
	if (substr_len > str_len)
		return 0;
		
	if (strncmp(str, substr, substr_len) == 0)
		return 1;
	else 
		return 0;
}

Node *max_difference(Tree *tree, const char *key)
{	
	Node *min = get_min(tree->root);
	int min_dif = strcmp(min->key, key);
	//printf("min: %d\n", min_dif);
	
	Node *max = get_max(tree->root);
	int max_dif = strcmp(max->key, key);
	//printf("max: %d\n", max_dif);

	if (abs(max_dif) > abs(min_dif))
		return max;
	else 
		return min;
}

Errors tree_delete(Tree *tree, const char *key)
{
	Node *del = NULL;
	Node *par = NULL;
	Node *node = tree->root;
	Node *right;
	
	if (find(node, key, &par, &del) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;

	if (del == tree->root) // если удаляемый элемент - корень
	{
		if (del->right == NULL) // у корня нет правого ребенка
		{
			tree->root = tree->root->left;
			return OK;
		}
		else // у корня есть правый ребенок
		{
			right = tree->root->right;
			if (right->tag == THREAD) // у правого ребенка нет левого ребенка
			{
				if (tree->root->tag == MAINLINK)
					right->tag = MAINLINK;
				right->left = tree->root->left;
				tree->root = right;
				return OK;
			}
			else // у правого ребенка есть левый ребенок
			{
				Node *succ = right->left;
				while(succ->tag == MAINLINK)
				{
					right = succ;
					succ = succ->left;
				}

				if (succ->right != NULL) // у наследника есть правый ребенок
					right->left = succ->right;
				else // у наследника нет правого ребенка
				{
					right->left = succ;
					right->tag = THREAD;
				}
				if (tree->root->tag == MAINLINK)
					succ->tag = MAINLINK;
				succ->left = tree->root->left;
				succ->right = tree->root->right;
				tree->root = succ;
				return OK;
			}
		}
		
	}

	if (del->tag == THREAD)
	{
		if (del->right == NULL) // лист, при удалении которого его нить переходит к родительскому
		{
			if (par->right == del)
				par->right = del->right;
			else // par->left == del
			{
				par->left = del->left;
				par->tag = THREAD;
			}
		}
		else // у узла есть правый ребенок
		{
			if (par->right == del)
				par->right = del->right;
			else // par->left == del
				par->left = del->left;

			right = del->right;
			while(right->tag == MAINLINK) // поиск минимального элемента правого поддерева
				right = right->left; 
			right->left = par;
		}
	}
	else // del->tag == MAINLINK
	{
		Node *left = del->left;
		if (left->right == NULL) // если у левого ребенка нет правого ребенка
		{
			left->right = del->right;
			if (left->right != NULL)
			{
				Node *tmp = del->left;
				while (tmp == MAINLINK) // поиск минимального элемента левого поддерева
					tmp = tmp->left;
				tmp->left = left;
			}
			if (par->right == del)
				par->right = left;
			else // par->left == del
				par->left = left;
		}
		else // если у левого ребенка есть правый ребенок
		{
			Node *max = left->right;
			for (; max->right != NULL; max = left->right) // находим максимальный элемент из левого поддерева удаляемого элемента
				left = max;

			if (max->tag == MAINLINK)
				left->right = max->left;
			else 
				left->right = NULL;

			max->left = del->left;
			if (max->left != NULL)
			{
				Node *tmp = del->right;
				while (tmp == MAINLINK)
					tmp = tmp->left;
				tmp->left = max;
			}
			max->right = del->right;
			max->tag = MAINLINK;
			if (par->right == del->right)
				par->right = max;
			else // par->left == del->left
				par->left = max;
		}
	}

	free(del->key);
	free(del);

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
	printf("%s: %d\n", node->key, node->info);

	if (node->tag == MAINLINK)
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

	if (node->tag == MAINLINK)
		free_node(node->left);

	free_node(node->right);
	free(node->key);
	free(node);
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

		int inf = atoi(info);
		int old;

		ins = tree_insert(tree, key, inf, &old);
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
