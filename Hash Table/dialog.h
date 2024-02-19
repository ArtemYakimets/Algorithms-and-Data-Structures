#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"

int dialog(const char **, int);
int add_element(Table *);
int delete_key_by_release(Table *);
int delete_key(Table *);
int find_element(Table *);
int show_table(Table *);
int import_table(Table *);
int search_key_by_release(Table *);
int search_key(Table *);
int clear_table(Table *);
int get_int(int *);
int get_char(char *);

#endif
