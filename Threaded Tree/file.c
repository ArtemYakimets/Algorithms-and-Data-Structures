#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "file.h"

char *freadline(FILE *file)
{
	char *ptr = (char *) calloc (1, sizeof(char));
	char buf[81];
	int n, len = 0;
	*ptr = '\0';

	do 
	{
		n = fscanf(file, "%80[^\n]", buf);
		if (n < 0)
		{
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
		 	fscanf(file, "%*c");
		 else 
		 {
		 	len += strlen(buf);
		 	ptr = (char *) realloc(ptr, len + 1);
		 	strcat(ptr, buf);
		 }
	} while (n > 0);

	return ptr;
}
