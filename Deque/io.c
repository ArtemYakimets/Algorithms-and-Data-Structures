#ifdef VECTOR_C
#include "vector.h"
#elif defined(LIST_C)
#include "list.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "io.h"

#define DELIM " \t"
#define PROMPT ""

int insert(Patient **pts, int *len) 
{
	int status;
	
	char *input = readline(PROMPT);
	if (!input || strcmp(input, "") == 0)
	{
		free(input);
		return 1;
	}

	char *saveptr1;
	char *patient = strtok_r(input, DELIM, &saveptr1);
	int p_len = strlen(patient);
	Patient tmp;

	while (patient != NULL)
	{	
		char *saveptr2;
		status = check_slashes(patient, p_len);
		if (status != 0)
		{
			free(input);
			free(*pts);
			return 1;
		}
		
		char *id = strtok_r(patient, "/", &saveptr2);
		if (id == NULL)
		{
			printf("Error: incorrect input\n");
			free(input);
			free(*pts);
			return 1;
		}
		int id_len = strlen(id);
		id[id_len] = '\0';
			
		char *str_ta = strtok_r(NULL, "/", &saveptr2);
		if (str_ta == NULL)
		{
			printf("Error: incorrect input\n");
			free(input);
			free(*pts);
			return 1;
		}
		int ta = atoi(str_ta);
		
		char *str_ts = strtok_r(NULL, DELIM, &saveptr2);
		if (str_ts == NULL)
		{
			printf("Error: incorrect input\n");
			free(input);
			free(*pts);
			return 1;
		}
		int ts = atoi(str_ts);
		
		status = check_int(ta, ts);
		if (status != 0)
		{
			free(input);
			free(*pts);
			return 1;
		}
		
		tmp = patient_input(id, ta, ts);	
		*pts = realloc (*pts, (*len + 1) * sizeof(Patient)); 
		(*pts)[*len] = tmp;
		++(*len);
	
		patient = strtok_r(NULL, DELIM, &saveptr1);
	}
	
	free(input);
	return 0;
}

int check_int(int ta, int ts)
{
	if ((ta <= 0) || (ts <= 0))
	{
		printf("Error: incorrect input\n");
		return 1;
	}	
	return 0;
}

int check_slashes(const char *patient, int p_len)
{
	int n = 0;
	
	for (int i = 0; i < p_len; ++i)
	{
		if (patient[i] == '/')
			n += 1;
	}

	if (n != 2)
	{
		printf("Error: incorrect input\n");
		return 1;
	}
	return 0;
}
