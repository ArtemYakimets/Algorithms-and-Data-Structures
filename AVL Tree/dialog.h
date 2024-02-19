#ifndef DIALOG_H
#define DIALOG_H

#include "tree.h"

int dialog(const char **, int);
int add_element(Tree *);
int delete_key(Tree *);
int find_element(Tree *);
int s_find_element(Tree *);
int traverse_tree(Tree *);
int print_tree(Tree *);
int import_tree(Tree *);
int get_int(int *);
int get_char(char *);

#endif
