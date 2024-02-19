#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patient.h"

Patient patient_input(char *id, int ta, int ts)
{
	Patient patient;
	patient.id = strdup(id);
	patient.ta = ta;
	patient.ts = ts;
	return patient;
}

void patient_print(const Patient patient)
{
	printf("%s", patient.id);
	//printf(" %d %d", patient.ta, patient.ts);
	printf(" ");
}

char *patient_delete_asterisk(char *id)
{
	int len = strlen(id);
	
	if (id[0] == '*')
	{
		for (int i = 0; i < len; i++)
			id[i] = id[i + 1];
		id = realloc (id, sizeof(char) * (len + 1));
	}
	return id;
}
