#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "table.h"
const char *menu[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Import", "6. Delete by range"};
const int menu_size = sizeof(menu) / sizeof(menu[0]);

int main() 
{
	int (*func[])(Table *) = {NULL, add_element, find_element, delete_element, show_table, import_table, task};

	Table table = {NULL, 0, 0, NULL};
	int opt;

	if (load_table(&table) == 0) 
		return 1;

	while (opt = dialog(menu, menu_size))
		if (!func[opt](&table))
			break;

	save(&table);
	
	printf("Goodbye!\n");
	delete_table(&table);
	return 0;
}
