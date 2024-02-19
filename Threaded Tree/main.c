#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "dialog.h"
#include "tree.h"
const char *menu[] = {"0. Quit", "1. Add", "2. Find", "3. Special find",
					 "4. Delete key", "5. Traverse", "6. Special traverse", 
					 "7. Import", "8. Show"};
const int menu_size = sizeof(menu) / sizeof(menu[0]);
 
int main() 
{
	int (*func[])(Tree *) = {NULL, add_element, find_element, s_find_element, delete_key, 
							traverse_tree, s_traverse_tree, import_tree, print_tree};

	Tree *tree = new_tree();
	
	int opt;

	while (opt = dialog(menu, menu_size))
		if (!func[opt](tree))
			break;

	printf("Goodbye!\n");
	free_tree(&tree);
	return 0;
}
