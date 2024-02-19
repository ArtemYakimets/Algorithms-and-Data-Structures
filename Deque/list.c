#ifdef LIST_C

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

Deque *new_deque(int SIZE) 
{
	Deque *tmp = (Deque *) malloc(sizeof(Deque));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp; 
}

void deque_delete(Deque **list) 
{
	Node *tmp = (*list)->head;
	Node *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->patient.id);
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

int push_front(Deque *list, Patient patient)
{
	Node *tmp = (Node *) malloc(sizeof(Node));
	if (tmp == NULL)
		return 1;
		
	 tmp->patient = patient;
	 tmp->next = list->head;
	 tmp->prev = NULL;
	 
	 if (list->head)
	 	list->head->prev = tmp;
	 list->head = tmp;

	 if (list->tail == NULL)
	 	list->tail = tmp;
	 list->size++;

	 return 0;
}

int pop_front(Deque *list, Patient *patient)
{
	(*patient) = patient_input(list->head->patient.id, list->head->patient.ta, list->head->patient.ts);
	Node *old;
	if (list->head == NULL)
		return 1;

	old = list->head;
	list->head = list->head->next;

	if (list->head)
		list->head->prev = NULL;

	if (old == list->tail)
		list->tail = NULL;

	free(old->patient.id);
	free(old);
	list->size--;
	return 0;
}

int push_back(Deque *list, Patient patient)
{
	Node *tmp = (Node *) malloc(sizeof(Node));
	if (tmp == NULL)
		return 1;
			
	tmp->patient = patient;
	tmp->next = NULL;
	tmp->prev = list->tail;

	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;

	if (list->head == NULL)
		list->head = tmp;
	list->size++;
	return 0;
}

int pop_back(Deque *list, Patient *patient)
{
	(*patient) = patient_input(list->tail->patient.id, list->tail->patient.ta, list->tail->patient.ts);
	Node *next;
	if (list->tail == NULL)
		return 1;

	next = list->tail;
	list->tail = list->tail->prev;
	
	if (next == list->tail)
		list->tail = NULL;

	free(next->patient.id);
	free(next);
	list->size--;
	return 0;
}


void deque_print(const Deque *list)
{
	Node *tmp = list->head;
	while (tmp)
	{
		patient_print(tmp->patient);
		tmp = tmp->next;
	}
	printf("\n");
}

Node *get_element(Deque *list, int index)
{
	Node *tmp = list->head;
	int i = 0;

	while(tmp && (i < index))
	{
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

/*
int deque_run (Patient **pts, int *len, Deque *deque)
{
	int ifprint, isempty = 1, time = 0;
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
					push_front(deque, patient);
				}
				else
					push_back(deque, patient);

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
				time = at_doctor.ts + i;
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
*/
#endif
