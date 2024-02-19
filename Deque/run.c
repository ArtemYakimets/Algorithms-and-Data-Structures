#ifdef VECTOR_C
#include "vector.h"
#elif defined(LIST_C)
#include "list.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include <string.h>

int deque_run (Patient **pts, int *len, Deque *deque)
{
	int ifprint, isempty = 1, time = 0, status;
	Patient patient;
	Patient at_doctor;
	at_doctor.id = (char *) calloc(1, sizeof(char));
	
	for (int i = 1; ; i++)
	{
		ifprint = 0;

		for (int j = 0; j < *len && j >= 0; j++)
		{
			if ((*pts)[j].ta == i)
			{				
				patient = patient_input((*pts)[j].id, (*pts)[j].ta, (*pts)[j].ts);
				free((*pts)[j].id);
				for (int k = j; k < *len - 1; k++)
				{
					(*pts)[k] = (*pts)[k + 1];
				}
				*pts = realloc (*pts, (*len - 1) * sizeof(Patient));
				--(*len);
				j--;

				if (patient.id[0] == '*')
				{
					patient.id = patient_delete_asterisk(patient.id);
					status = push_front(deque, patient);
					if (status == 1)
					{
						free(patient.id);
					}
				}
				else
				{
					status = push_back(deque, patient);
					if (status == 1)
					{
						free(patient.id);
					}
				}
				
				ifprint = 1;
			}
		}
		
		if (isempty == 1)
		{
			free(at_doctor.id);
			at_doctor.id = NULL;
			
			if (deque->size != 0)
			{
				pop_front(deque, &at_doctor);
				time = at_doctor.ts + i - 1;
				isempty = 0;
				ifprint = 1;
			}
			else if (deque->size == 0 && *len == 0)
				break;
		}
		if (time == i)
			isempty = 1;	

		if (ifprint == 1)
		{
			printf("%d\n", i);
			printf("%s\t", at_doctor.id);
			deque_print(deque);
			printf("\n");
		}
	}
	return 0;
}
