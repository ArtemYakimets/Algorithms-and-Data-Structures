#ifndef TABLE_H
#define TABLE_H

#include "file.h"

typedef struct Item {
	char *info;
} Item;

typedef struct KeySpace {
	char *key;
	Item *info;
} KeySpace;

typedef struct Table {
	KeySpace *ks;
	int msize;
	int csize;
} Table;

typedef enum Errors {
	OK,
	OVERFLOW,
	KEY_NOT_FOUND,
	DUPLICATE_KEY,
	FILE_NOT_FOUND
} Errors;

Table *new_table(int);
void bounds(const Table *, const char *, int *, int *);
Errors insert(Table *, const char *, const char *);
Errors delete(Table *, const char *);
Errors find(const Table *, const char *, char **);
Errors import (Table *, const char*);
Errors delete_by_range(Table *, const char *, const char *);
void print_table(const Table *);
void delete_table(Table **);

#endif
