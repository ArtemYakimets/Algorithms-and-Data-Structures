#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "table.h"

Errors find(const Table *table, const char *key)
{
	int left, right;
	if (bounds(table, key, &left, &right) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;

	char *buf = malloc((table->ks[left].key_len + table->ks[left].info_len)  * sizeof(char));
	fseek(table->file, table->ks[left].key_offset, SEEK_SET);
	fread(buf, sizeof(char), table->ks[left].key_len + table->ks[left].info_len, table->file);

	printf("key: ");
	for (int j = 0; j < table->ks[left].key_len; j++)
		printf("%c", buf[j]);
	printf("\nitem: ");
	for (int j = table->ks[left].key_len; j < table->ks[left].key_len + table->ks[left].info_len; j++)
		printf("%c", buf[j]);
	printf("\n\n");
	free(buf);

	return OK;
}

Errors bounds(const Table *table, const char *key, int *left, int *right)
{
	int middle;
	*left = -1;
	*right = table->csize;
	char *k;

	while (*right > *left + 1)
	{
		middle = (*left + *right) / 2;

		k = malloc(table->ks[middle].key_len + 1);
		fseek(table->file, table->ks[middle].key_offset, SEEK_SET);
		fread(k, sizeof(char), table->ks[middle].key_len, table->file);
		k[table->ks[middle].key_len] = '\0';

		if (strcmp(k, key) > 0)
			*right = middle;
		else 
			*left = middle;

		free(k); 				
	}

	if (*left >= 0) 
	{
	k = malloc(table->ks[*left].key_len + 1);
	fseek(table->file, table->ks[*left].key_offset, SEEK_SET);
	fread(k, sizeof(char), table->ks[*left].key_len, table->file);
	k[table->ks[*left].key_len] = '\0';
	}

	if (*right == 0 || k == NULL || strcmp(k, key) != 0)
		return KEY_NOT_FOUND;

	return OK;
}
Errors load(Table *table, const char *name)
{
	table->file = fopen(name, "r+b");
	if (table->file == NULL)
		return FILE_NOT_FOUND;

	fread(&table->msize, sizeof(int), 1, table->file);
	table->ks = (KeySpace *) calloc(table->msize, sizeof(KeySpace));
	
	fread(&table->csize, sizeof(int), 1, table->file);
	fread(table->ks, sizeof(KeySpace), table->csize, table->file);
	
	return OK;
}

Errors create(Table *table, const char *name, int msize)
{
	table->msize = msize;
	table->csize = 0;
	table->file = fopen(name, "w+b");
	if (table->file == NULL)
	{
		table->ks = NULL;
		return FILE_NOT_FOUND;
	}

	table->ks = (KeySpace *) calloc(table->msize, sizeof(KeySpace));
	fwrite(&table->msize, sizeof(int), 1, table->file);
	fwrite(&table->csize, sizeof(int), 1, table->file);
	fwrite(table->ks, sizeof(KeySpace), table->msize, table->file);
	
	return OK;	
}
Errors insert(Table *table, const char *key, const char *info)
{
	int left, right;
	
	if (table->csize == table->msize)
		return OVERFLOW;

	if (bounds(table, key, &left, &right) != KEY_NOT_FOUND)
		return DUPLICATE_KEY;

	memmove(table->ks + right + 1, table->ks + right, sizeof(KeySpace) * (table->csize - right));
	
	table->ks[right].key_len = strlen(key);
	fseek(table->file, 0, SEEK_END);
	table->ks[right].key_offset = ftell(table->file);
	
	table->ks[right].info_len = strlen(info);

	fwrite(key, sizeof(char), table->ks[right].key_len, table->file);
	fwrite(info, sizeof(char), table->ks[right].info_len, table->file);

	++(table->csize);

	return OK;	
}

Errors save(Table *table)
{
	fseek(table->file, sizeof(int), SEEK_SET);
	fwrite(&table->csize, sizeof(int), 1, table->file);
	fwrite(table->ks, sizeof(KeySpace), table->csize, table->file);

	fclose(table->file);
	table->file = NULL;
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
			return(ins);
		}
		free(key);
		free(info);
	}
	fclose(file);
	return OK;
}

Errors delete_by_range(Table *table, const char *lower, const char *upper)
{
	int left, right, low, n, up;
	if (bounds(table, lower, &left, &right) == KEY_NOT_FOUND)
		low = right;
	else
		low = left;

	if (low == table->csize)
		return OK;

	if (bounds(table, upper, &left, &right) == KEY_NOT_FOUND)
		up = table->csize - 1;
	else
		up = left;
		
	n = up + 1;

	if (!((n == table->csize) && (table->msize == table->csize)))
		memmove(table->ks + low, table->ks + n, sizeof(KeySpace) * (table->msize - n));

	int del_num = n - low;
	table->csize = table->csize - del_num;
	return OK;
}

Errors delete(Table *table, const char *key)
{
	int left, right;
	if (bounds(table, key, &left, &right) == KEY_NOT_FOUND)
		return KEY_NOT_FOUND;

	memmove(table->ks + left, table->ks + left + 1, sizeof(KeySpace) * table->csize - left - 1);
	--(table->csize);
	
	return OK;
}

void print_table(const Table *table)
{
	char *buf;
	fseek(table->file, sizeof(int), SEEK_SET);

	for (int i = 0; i < table->csize; i++)
	{
		buf = malloc((table->ks[i].key_len + table->ks[i].info_len)  * sizeof(char));
		fseek(table->file, table->ks[i].key_offset, SEEK_SET);
		fread(buf, sizeof(char), table->ks[i].key_len + table->ks[i].info_len, table->file);

		printf("%d\n", i);
		printf("key: ");
		for (int j = 0; j < table->ks[i].key_len; j++)
			printf("%c", buf[j]);
		printf("\nitem: ");
		for (int j = table->ks[i].key_len; j < table->ks[i].key_len + table->ks[i].info_len; j++)
			printf("%c", buf[j]);
		printf("\n\n");
		free(buf);
	}	
}

void delete_table(Table *table)
{
	free(table->ks);
}
