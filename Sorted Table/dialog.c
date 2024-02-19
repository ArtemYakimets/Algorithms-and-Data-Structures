#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "table.h"

#define DELIM " \t"
#define PROMPT ""

const char *errs[] = {"Ok!", "Error: Overflow!", "Error: Key not found!", "Error: Duplicate key!", "Error: File not found!"};

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

int add_element(Table *table)
{
	printf("Enter the key:\n");
	char *key = readline(PROMPT);
	if (!key || strcmp(key, "") == 0)
	{
		free(key);
		return 0;
	}

	printf("Enter the info:\n");
	char *info = readline(PROMPT);
	if (!info || strcmp(info, "") == 0)
	{
		free(info);
		return 0;
	}

	int status = insert(table, key, info);
	printf("%s\n", errs[status]);
		
	free(key);
	free(info);	

	return 1;
}

int delete_element(Table *table)
{	
	if (table->csize == 0)
		printf("Error: There is no table here!\n");
	else 
	{
		printf("Enter the key:\n");
		char *key = readline(PROMPT);
		if (!key || strcmp(key, "") == 0)
		{
			free(key);
			return 0;
		}

		int status = delete(table, key);
		printf("%s\n", errs[status]);
		free(key);
	}
	return 1;
}

int find_element(Table *table)
{
	char *info;
	if (table->csize == 0)
		printf("Error: There is no table here!\n");
	else
	{
		printf("Enter the key:\n");
		char *key = readline(PROMPT);
		if (!key || strcmp(key, "") == 0)
		{
			free(key);
			return 0;
		}

		int status = find(table, key, &info);
		if (status == OK)
		{
			printf("key: %s\n", key);
			printf("item: %s\n", info);
			free(info);
		}
		printf("%s\n", errs[status]);
		free(key);
	}	
	return 1;
}

int show_table(Table *table)
{
	if (table->csize == 0)
		printf("Error: There is no table here!\n");
	else
	{
		printf("Here is the table:\n\n");
		print_table(table);
	}
	return 1;
}

int import_table(Table *table)
{
	printf("Enter the name of file:\n");
	char *name = readline(PROMPT);
	if (!name || strcmp(name, "") == 0)
	{
		free(name);
		return 0;
	}
	
	int status = import(table, name);
	printf("%s\n", errs[status]);
	free(name);

	return 1;
}

int task(Table *table)
{		
	if (table->csize == 0)
		printf("Error: There is no table here!\n");
	else
	{
		printf("Enter the lower bound key:\n");
		char *key1 = readline(PROMPT);
		if (!key1 || strcmp(key1, "") == 0)
		{
			free(key1);
			return 0;
		}

		printf("Enter the upper bound key:\n");
		char *key2 = readline(PROMPT);
		if (!key2 || strcmp(key2, "") == 0)
		{
			free(key2);
			return 0;
		}

		if (strcmp(key1, key2) > 0)
		{
			printf("Error: Incorrect values\n");
			return 0;
			
		}

		int status = delete_by_range(table, key1, key2);
		printf("%s\n", errs[status]);
		free(key1);	
		free(key2);	
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

		printf("Error: Not a number entered!\n");
		scanf("%*[^\n]");
		flag = scanf("%d", n);
	}
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

