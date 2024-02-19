#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "table.h"

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

int add_element(Table *table)
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

	int status = insert(table, key, info);
	printf("%s\n", errs[status]);
		
	free(info);	

	return 1;
}

int delete_key_by_release(Table *table)
{	
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	printf("Enter the release:\n");
	int release;
	if(get_int(&release) == 0)
		return 0;

	int status = delete_release(table, key, release);
	printf("%s\n", errs[status]);
	
	return 1;
}

int delete_key (Table *table)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	int status = delete(table, key);
	printf("%s\n", errs[status]);
	
	return 1;
}

int find_element(Table *table)
{
	KeySpace *prev, *cur;
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	int status = find(table, key, &prev, &cur);
	if (status == OK)
	{
		printf("key: %d\n", cur->key);
		printf("item: %s\n", cur->info->info);
	}
	printf("%s\n", errs[status]);
		
	return 1;
}

int show_table(Table *table)
{
	printf("Here is the table:\n\n");
	print_table(table);

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

int search_key_by_release(Table *table)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	printf("Enter the release:\n");
	int release;
	if(get_int(&release) == 0)
		return 0;

	Table *new = new_table(1);
	int status = search_release(table, new, key, release);
	if (status == 0)
	{
		printf("\nHere is the new table:\n\n");
		print_table(new);
	}
	printf("%s\n", errs[status]);
	delete_table(&new);
	
	return 1;
}

int search_key(Table *table)
{
	printf("Enter the key:\n");
	int key;
	if(get_int(&key) == 0)
		return 0;

	Table *new = new_table(1);
	int status = search(table, new, key);

	if (status == 0)
	{
		printf("\nHere is the new table:\n\n");
		print_table(new);
	}
	printf("%s\n", errs[status]);
	delete_table(&new);
	
	return 1;
}

int clear_table(Table *table)
{
	int status = clear(table);
	printf("%s\n", errs[status]);
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

