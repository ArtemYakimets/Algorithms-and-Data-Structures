#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "graph.h"
const char *menu[] = {"0. Quit", "1. Add vertex", "2. Add edge", 
					 "3. Find vertex", "4. Find edge", 
					 "5. Delete vertex", "6. Delete edge", 
					 "7. Change vertex type", "8. Find path to the end",
					 "9. Show"};
const int menu_size = sizeof(menu) / sizeof(menu[0]);
 
int main() 
{
	int (*func[])(Graph *) = {NULL, add_vertex, add_edge, 
							vertex_find, edge_find, 
							delete_vertex, delete_edge, 
							change_vertex, traversal, 
							print_graph};

	Graph *graph = new_graph();
	
	int opt;

	while (opt = dialog(menu, menu_size))
		if (!func[opt](graph))
			break;

	printf("Goodbye!\n");
	free_graph(&graph);
	return 0;
}
