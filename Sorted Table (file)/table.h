#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include "file.h"

typedef struct KeySpace {
	int key_offset;
	int key_len;
	int info_len;
} KeySpace;

typedef struct Table {
	KeySpace *ks;
	int msize;
	int csize;
	FILE *file;
} Table;

typedef enum Errors {
	OK,
	OVERFLOW,
	KEY_NOT_FOUND,
	DUPLICATE_KEY,
	FILE_NOT_FOUND,
	FILE_ALREADY_EXISTS
} Errors;

Errors find(const Table *, const char *);
Errors bounds(const Table *, const char *, int *, int *);
Errors load(Table *, const char *);
Errors create(Table *, const char *, int);
Errors insert(Table *, const char *, const char *);
Errors save(Table *);
Errors import(Table *, const char *);
Errors delete(Table *, const char *);
Errors delete_by_range(Table *, const char *, const char *);
void print_table(const Table *);
void delete_table(Table *);

#endif
