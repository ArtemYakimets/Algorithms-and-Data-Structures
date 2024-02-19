#ifndef TABLE_H
#define TABLE_H

#include "file.h"

typedef enum Errors 
{
	OK,
	KEY_NOT_FOUND,
	FILE_NOT_FOUND
} Errors;

typedef struct Item {
	char *info;
} Item;

typedef struct KeySpace {
	int key;
	Item *info;
	struct KeySpace *next;
	int release;
} KeySpace;

typedef struct Table {
	int msize;
	KeySpace **ks;
} Table;

Table *new_table(int);
int hash(const int);
Errors find(const Table *, const int, KeySpace **, KeySpace **);
Errors insert(Table *, const int, const char *); 
Errors delete_release(Table *, const int, const int);
Errors delete(Table *, const int);
Errors import(Table *, const char *);
Errors search_release(const Table *, Table *, const int, const int);
Errors search(const Table *, Table *, int);
Errors clear(Table *);
void print_table(const Table *);
void delete_table(Table **);

#endif
