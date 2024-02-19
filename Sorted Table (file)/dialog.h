#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"

int dialog(const char **, int);
int load_table(Table *);
int add_element(Table *);
int delete_element(Table *);
int find_element(Table *);
int show_table(Table *);
int import_table(Table *);
int task(Table *);
int get_int(int *);
int get_char(char *);

#endif
