#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "table.h"

#define DELIM " \t"
#define PROMPT ""

Table *new_table(int sz)
{
	Table *table = (Table *) calloc (1, sizeof(Table));
	table->msize = sz;
	table->csize = 0;
	table->ks = (KeySpace *) calloc(table->msize, sizeof(KeySpace));

	return table; 
}

void bounds(const Table *table, const char *key, int *left, int *right)
{
	int middle;		
	*left = -1; 
	*right = table->csize;
	while (*right > *left + 1)
	{
		middle = (*left + *right) / 2;
		if (strcmp(table->ks[middle].key, key) == 1)
			*right = middle;
		else	
			*left = middle;
	}	
}

Errors insert(Table *table, const char *key, const char* info)
{
	if (table->csize == table->msize)
		return OVERFLOW;
	
	int left, right;
	bounds(table, key, &left, &right);
	
	if (left >= 0) 
	{
		if (strcmp(table->ks[left].key, key) == 0)
			return DUPLICATE_KEY;
	}

	memmove(table->ks + right + 1, table->ks + right, sizeof(KeySpace) * (table->csize - right));	

	KeySpace *a = (table->ks) + right;
	a->info = (Item *) calloc (1, sizeof(Item));
	a->info->info = strdup(info);
	a->key = strdup(key);

	++(table->csize);
	
	return OK;
}

Errors delete(Table *table, const char *key)
{
	int left, right;
	bounds(table, key, &left, &right);

	if (left >= 0) 
	{
		if (strcmp(table->ks[left].key, key) == 0)
		{	
			free(table->ks[left].info->info);
			free(table->ks[left].info);
			free(table->ks[left].key);
			
			memmove((table->ks) + left, (table->ks) + left + 1, sizeof(KeySpace) * (table->csize - left - 1));
			
			memset(table->ks + (table->csize - 1), 0, sizeof(KeySpace));
			--(table->csize);
		}
		else 
			return KEY_NOT_FOUND;
	}
	return OK;
}

Errors find(const Table *table, const char *key, char **info)
{
	int left, right;
	bounds(table, key, &left, &right);

	if (left >= 0) 
	{
		if (strcmp(table->ks[left].key, key) == 0)
			*info = strdup(table->ks[left].info->info);
		else
			return KEY_NOT_FOUND;
	}
	return OK;	
}

Errors import(Table *table, const char *name)
{
	FILE *file = fopen(name, "r");

	if (file == NULL)
		return FILE_NOT_FOUND;

	char *key; 
	char *info;
	int ins;

	for (;;)
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

		ins = insert(table, key, info);
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

Errors delete_by_range(Table *table, const char *lower, const char *upper)
{
	int left, right, low, up, n;
	bounds(table, lower, &left, &right);
	
	if (left >= 0)
	{
		if (strcmp(table->ks[left].key, lower) == 0)
			low = left;
		else 
			low = right;
	}
	else
		low = right;

	if (low == table->csize)
		return OK;

	bounds(table, upper, &left, &right);

	if (left >= 0)
	{
		if (strcmp(table->ks[left].key, upper) == 0)
			up = left;
		else 
			up = table->csize - 1;
	}
	else
		up = right;
	
	for (int i = low; i <= up; i++)
	{
		n = i;
		
		free(table->ks[i].info->info);
		free(table->ks[i].info);
		free(table->ks[i].key);
	}
	n++;
	
	if (!((n == table->csize) && (table->msize == table->csize)))
		memmove(table->ks + low, table->ks + n, sizeof(KeySpace) * (table->msize - n));
	
	int del_num = n - low;
	table->csize = table->csize - del_num;

	memset(table->ks + (table->msize - del_num), 0, sizeof(KeySpace) * del_num);

	return OK;
}

void delete_table(Table **table)
{
	for (int i = 0; i < (*table)->msize; i++)
	{
		if ((*table)->ks[i].info)
		{
			free((*table)->ks[i].info->info);
			free((*table)->ks[i].info);
		}
		free((*table)->ks[i].key);
	}

	free((*table)->ks);
	free(*table);
}

void print_table(const Table *table)
{
	for (int i = 0; i < table->msize; i++)
	{
		if (i == table->csize)
			printf("============================================\n\n");
			
		printf("%d\n", i);
		
		if (!table->ks[i].key)
			printf("key: (null)\n");
		else
			printf("key: %s\n", table->ks[i].key);

		if (!table->ks[i].info)
			printf("item: (null)\n\n");
		else
			printf("item: %s\n\n", table->ks[i].info->info);
	}
}
