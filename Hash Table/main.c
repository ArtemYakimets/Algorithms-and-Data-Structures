#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "table.h"
const char *menu[] = {"0. Quit", "1. Add", "2. Find", "3. Delete key (by release)", 
						"4. Delete key", "5. Show", "6. Import", "7. Search key (by release)",
						"8. Search key", "9. Clear table"};
const int menu_size = sizeof(menu) / sizeof(menu[0]);

int main() 
{
	int (*func[])(Table *) = {NULL, add_element, find_element, delete_key_by_release, 
							delete_key, show_table, import_table, search_key_by_release, 
							search_key, clear_table};

	int msize;
	printf("Enter the maximum size:\n");
	int status = get_int(&msize);
	if (status == 0)
		return 1;
	while(msize <= 0)
	{
		printf("Error: Size must be greater than 0!\n");
		int status = get_int(&msize);
		if (status == 0)
			return 1;
	}
	Table *table = new_table(msize);
	int opt;

	while (opt = dialog(menu, menu_size))
		if (!func[opt](table))
			break;

	printf("Goodbye!\n");
	delete_table(&table);
	return 0;
}
