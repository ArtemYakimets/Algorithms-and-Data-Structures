#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>

#include "table.h"

Table *new_table(int sz)
{
	Table *table = (Table *) calloc (1, sizeof(Table));
	table->msize = sz;
	table->ks = (KeySpace **) calloc (table->msize, sizeof(KeySpace));
	for (int i = 0; i < table->msize; i++)
		table->ks[i] = NULL;

	return table;
}

int hash(const int key)
{
	int hash = INT_MAX;
	for (int i = 0; i < sizeof(key); ++i)
		hash = 37 * hash + ((key >> 8 * i) & 0xff);	

	return abs(hash);
}

Errors find(const Table *table, const int key, KeySpace **prev, KeySpace **cur)
{
	int i = hash(key) % table->msize;
	*prev = NULL;
	for (KeySpace *tmp = table->ks[i]; tmp != NULL; tmp = tmp->next)
	{
		if (tmp->key == key)
		{
			*cur = tmp;
			return OK;
		}
		*prev = tmp;
	}
	return KEY_NOT_FOUND;
}

Errors insert(Table *table, const int key, const char *info)
{
	int i = hash(key) % table->msize;
	KeySpace *tmp = table->ks[i];
	KeySpace *prev = NULL;
	KeySpace *new = (KeySpace *) malloc(sizeof(KeySpace));
	new->key = key;
	new->release = 1;
	new->info = (Item *) malloc(sizeof(Item));
	new->info->info = strdup(info);

	while (tmp != NULL && tmp->key < key)
	{
		prev = tmp;
		tmp = tmp->next;
	}

	if (prev != NULL)
	{
		prev->next = new;
		new->next = tmp;
	}
	else 
	{
		new->next = table->ks[i];
		table->ks[i] = new;
	}
	
	if (tmp != NULL && tmp->key == new->key)
		new->release = tmp->release + 1;

	return OK;
}

Errors delete_release(Table *table, const int key, const int release)
{
	int i = hash(key) % table->msize;
	KeySpace *tmp, *prev;
	
	if (find(table, key, &prev, &tmp) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;
		
	while ((tmp != NULL) && (tmp->key <= key) && !(tmp->key == key && tmp->release == release))
	{
		prev = tmp;
		tmp = tmp->next;
	}

	if ((tmp == NULL) || (tmp->key > key)) 
	 	return KEY_NOT_FOUND;

	if (tmp == table->ks[i])
		table->ks[i] = table->ks[i]->next;
	else
		prev->next = tmp->next;

	free(tmp->info->info);
	free(tmp->info);
	free(tmp);
	
	return OK;
}

Errors delete(Table *table, const int key)
{
	int i = hash(key) % table->msize;
	KeySpace *tmp, *prev;
	
	if (find(table, key, &prev, &tmp) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;
		
	while ((tmp != NULL) && (tmp->key == key))
	{
		KeySpace *del = tmp;
		tmp = tmp->next;
		if (del == table->ks[i])
			table->ks[i] = table->ks[i]->next;
		else 
			prev->next = del->next;

		free(del->info->info);
		free(del->info);
		free(del);		
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
	int ins, k;

	for (;;)
	{
		key = freadline(file);
		if (key == NULL)
			break;
		k = atoi(key);

		info = freadline(file);
		if (info == NULL)
		{
			free(key);
			break;
		}

		ins = insert(table, k, info);
		if (ins != OK)
		{
			free(key);
			free(info);
			fclose(file);
			return ins;
		}
		free(key);
		free(info);
	}
	fclose(file);
	
	return OK;
}

Errors search_release(const Table *table, Table *new, const int key, const int release)
{
	KeySpace *tmp, *prev;

	if (find(table, key, &prev, &tmp) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;
		
	while ((tmp != NULL) && (tmp->key <= key) && !(tmp->key == key && tmp->release == release))
		tmp = tmp->next;

	if ((tmp == NULL) || (tmp->key > key))
	 	return KEY_NOT_FOUND;

	insert(new, tmp->key, tmp->info->info);
	
	return OK;
}

Errors search(const Table *table, Table *new, int key)
{
	KeySpace *tmp, *prev;

	if (find(table, key, &prev, &tmp) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;
	
	while ((tmp != NULL) && (tmp->key == key))
	{
		insert(new, tmp->key, tmp->info->info);	
		tmp = tmp->next;
	}
	
	return OK;
}

Errors clear(Table *table)
{
	for (int i = 0; i < table->msize; i++)
	{
		KeySpace *tmp = table->ks[i];
		KeySpace *prev = NULL;
				
		while (tmp != NULL)
		{
			if (prev != NULL)
			{
				if (tmp->key == prev->key)
				{
					KeySpace *del = tmp;
					tmp = tmp->next;
					prev->next = del->next;

					free(del->info->info);
					free(del->info);
					free(del);
				}
				else
				{
					prev = tmp;
					tmp = tmp->next;
				}
			}
			else 
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return OK;
}

void print_table(const Table *table)
{
	printf("Size: %d\n\n", table->msize);
	for (int i = 0; i < table->msize; i++)
	{
		printf("============================\n");
		printf("%d\n\n", i);
		
		KeySpace *tmp = table->ks[i];

		while(tmp != NULL)
		{
			printf("key: %d\n", tmp->key);
			printf("release: %d\n", tmp->release);
			printf("item: %s\n\n", tmp->info->info);

			tmp = tmp->next;
		}
	}
}

void delete_table(Table **table)
{
	for (int i = 0; i < (*table)->msize; i++)
	{
		KeySpace *tmp =  (*table)->ks[i];
		KeySpace *next = NULL;

		while(tmp != NULL)
		{
			next = tmp->next;
			free(tmp->info->info);
			free(tmp->info);
			free(tmp);
			tmp = next;
		}
	}

	free((*table)->ks);
	free(*table);
}
