#ifndef LINE_H
#define LINE_H

typedef struct Line{
	int size;
	int *data;
} Line;

void line_print(Line );
int line_insert(Line *);

#endif
