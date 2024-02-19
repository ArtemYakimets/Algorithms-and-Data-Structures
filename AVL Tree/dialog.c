#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "tree.h"

#define DELIM " \t"
#define PROMPT ""

const char *errs[] = {"Ok!", "Error: Key not found!", "Error: File not found!"};

int dialog(const char *menu[], int menu_size)
{
	char *errmsg = "";
	int choice, status;

	do 
	{
		puts(errmsg);
		errmsg = "Error: Incorrect number entered! Try again";

		for (int i = 0; i < menu_size; i++)
			puts(menu[i]);

		puts("Enter the number of choice:");

		status = get_int(&choice);
		if (status == 0)
			choice = 0;
	} while (choice < 0 || choice >= menu_size);

	return choice;
}

int add_element(Tree *tree)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	printf("Enter the info:\n");
	char *info = readline(PROMPT);
	if (!info || strcmp(info, "") == 0)
	{
		free(info);
		return 0;
	}

	int status = tree_insert(tree, key, info);
	printf("%s\n", errs[status]);
		
	free(info);	

	return 1;
}

int delete_key (Tree *tree)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	printf("Enter the release:\n");
	int release;
	if(get_int(&release) == 0)
		return 0;

	int status = tree_delete(tree, key, release);
	printf("%s\n", errs[status]);		
	return 1;
}


int find_element(Tree *tree)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	printf("Enter the release:\n");
	int release;
	if(get_int(&release) == 0)
		return 0;
		
	Node *node;
	Item *found;
	int status = tree_find(tree, key, release, &node, &found, 0);
	if (status == OK)
	{
		printf("key: %d\n", key);
		printf("release: %d\n", release);
		printf("item: %s\n", found->info);
	}
	printf("%s\n", errs[status]);		
	return 1;
}


int s_find_element(Tree *tree)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	int release = 0;
	Node *node;
	Item *found;
	int status = tree_find(tree, key, release, &node, &found, 1);
	if (status == OK)
	{
		Item *p = node->head;
		while (p != NULL)
		{
			printf("key: %d\n", node->key); 
			printf("release: %d\n", p->release);
			printf("item: %s\n\n", p->info);
			p = p->next;
		}
	}
	printf("%s\n", errs[status]);		
	return 1;
}


int traverse_tree(Tree *tree)
{
	printf("Here is the tree:\n\n");
	tree_traversal(tree->root);

	return 1;
}


int print_tree(Tree *tree)
{
	printf("Here is the tree:\n\n");
	tree_print(tree->root, 0);

	return 1;
}

int import_tree(Tree *tree)
{
	printf("Enter the name of file:\n");
	char *name = readline(PROMPT);
	if (!name || strcmp(name, "") == 0)
	{
		free(name);
		return 0;
	}
	
	int status = tree_import(tree, name);
	printf("%s\n", errs[status]);
	free(name);

	return 1;
}

int get_char(char *n)
{
	int flag = scanf("%c", n);

	while (flag != 1)
	{
		if (flag == EOF)
			return 0;

		printf("Error: Not a char entered!\n");
		scanf("%*[^\n]");
		flag = scanf("%c", n);
	}

	return 1;
}

int get_int(int *n)
{
	int flag = scanf("%d", n);

	while (flag != 1)
	{
		if (flag == EOF)
			return 0;
			
		printf("Incorrect number entered!\nTry again:\n");
		scanf("%*[^\n]");
		flag = scanf("%d", n);
	}
	
	while (*n < 0)
	{
		printf("The number must be a non-negative number!\nTry again:\n");
		flag = scanf("%d", n);

		if (flag == EOF)
			return 0;
	}
	return 1;
}

