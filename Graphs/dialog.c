#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "graph.h"

#define DELIM " \t"
#define PROMPT ""

const char *errs[] = {"Ok!", "Error: Vertex not found!", "Error: Vertex already exists!",
					  "Error: Edge not found!", "Error: Edge already exists!",
					  "Error: Not a neighboring vertex!"};

int dialog(const char *menu[], int menu_size)
{
	char *errmsg = "";
	int choice, status;

	do 
	{
		puts(errmsg);
		errmsg = "Error: Incorrect number entered! Try again";

		for (int i = 0; i < menu_size; i++)
			puts(menu[i]);

		puts("Enter the number of choice:");

		status = get_int(&choice);
		if (status == 0)
			choice = 0;
	} while (choice < 0 || choice >= menu_size);

	return choice;
}

int add_vertex(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x;
	if(get_int(&x) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y;
	if(get_int(&y) == 0)
		return 0;

	printf("Enter the type of vertex:\n");
	printf("[s]: start\n");
	printf("[e]: end\n");
	printf("[o]: ordinary\n");
	char t;
	if(get_char(&t) == 0)
		return 0;

	Type type;
	if (t == 's')
		type = START;
	else if (t == 'e')
		type = END;
	else 
		type = ORDINARY;
		
	int status = graph_new_vertex(graph, x, y, type);
	printf("%s\n", errs[status]);	

	return 1;
}

int add_edge(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x1;
	if(get_int(&x1) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y1;
	if(get_int(&y1) == 0)
		return 0;

	printf("Enter the x-coordinate:\n");
	int x2;
	if(get_int(&x2) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y2;
	if(get_int(&y2) == 0)
		return 0;

	int status = graph_new_edge(graph, x1, y1, x2, y2);
	printf("%s\n", errs[status]);	

	return 1;
}

int vertex_find(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x;
	if(get_int(&x) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y;
	if(get_int(&y) == 0)
		return 0;

	List *a = NULL;
	List *prev_a = NULL;
	int status = graph_find_vertex(graph, x, y, &a, &prev_a);
	if (status == OK)
	{
		printf("(%d, %d)\n", a->vertex->x, a->vertex->y);
		char *type = get_type(a->vertex->type);
		printf("%s\n", type);
		free(type);
	}
	printf("%s\n", errs[status]);	

	return 1;
}

int edge_find(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x1;
	if(get_int(&x1) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y1;
	if(get_int(&y1) == 0)
		return 0;

	printf("Enter the x-coordinate:\n");
	int x2;
	if(get_int(&x2) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y2;
	if(get_int(&y2) == 0)
		return 0;

	Vertex *a = NULL;
	Vertex *b = NULL;
	int status = graph_find_edge(graph, x1, y1, x2, y2, &a, &b);
	if (status == OK)
	{
		printf("(%d, %d)", a->x, a->y);
		printf(" --- ");
		printf("(%d, %d)\n", b->x, b->y);
	}
	printf("%s\n", errs[status]);	

	return 1;
}


int delete_vertex(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x;
	if(get_int(&x) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y;
	if(get_int(&y) == 0)
		return 0;
		
	int status = graph_delete_vertex(graph, x, y);
	printf("%s\n", errs[status]);	

	return 1;
}


int delete_edge(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x1;
	if(get_int(&x1) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y1;
	if(get_int(&y1) == 0)
		return 0;

	printf("Enter the x-coordinate:\n");
	int x2;
	if(get_int(&x2) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y2;
	if(get_int(&y2) == 0)
		return 0;

	int status = graph_delete_edge(graph, x1, y1, x2, y2);
	printf("%s\n", errs[status]);	

	return 1;
}

int change_vertex(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x;
	if(get_int(&x) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y;
	if(get_int(&y) == 0)
		return 0;
		
	printf("Enter the type of vertex:\n");
	printf("[s]: start\n");
	printf("[e]: end\n");
	printf("[o]: ordinary\n");
	char t;
	if(get_char(&t) == 0)
		return 0;

	Type type;
	if (t == 's')
		type = START;
	else if (t == 'e')
		type = END;
	else 
		type = ORDINARY;	
	int status = graph_change_vertex(graph, x, y, type);
	printf("%s\n", errs[status]);	

	return 1;
}

int traversal(Graph *graph)
{
	printf("Enter the x-coordinate:\n");
	int x;
	if(get_int(&x) == 0)
		return 0;

	printf("Enter the y-coordinate:\n");
	int y;
	if(get_int(&y) == 0)
		return 0;	

	int status = depth_first_search(graph, x, y);
	printf("%s\n", errs[status]);
}

int print_graph(Graph *graph)
{
	printf("Here is the graph:\n\n");
	graph_print(graph);

	return 1;
}

char *get_type(Type t)
{
	char *type = NULL;
	if (t == START)
		type = "START";
	else if (t == END)
		type = "END";
	else
		type = "ORDINARY";
	return type;
}

int get_char(char *n)
{
	int flag = scanf("%c", n);

	while (flag != 1)
	{
		if (flag == EOF)
			return 0;

		printf("Error: Not a char entered!\n");
		scanf("%*[^\n]");
		flag = scanf("%c", n);
	}

	while ((*n != 's') && (*n != 'e') && (*n != 'o'))
	{
		printf("You must enter 's', 'e' or 'o'!\n");
		flag = scanf("%c", n);

		if (flag == EOF)
			return 0;
	}

	return 1;
}

int get_int(int *n)
{
	int flag = scanf("%d", n);

	while (flag != 1)
	{
		if (flag == EOF)
			return 0;
			
		printf("Incorrect number entered!\nTry again:\n");
		scanf("%*[^\n]");
		flag = scanf("%d", n);
	}
	
	while (*n < 0)
	{
		printf("The number must be a non-negative number!\nTry again:\n");
		flag = scanf("%d", n);

		if (flag == EOF)
			return 0;
	}
	return 1;
}

