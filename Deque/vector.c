#ifdef VECTOR_C

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Deque *new_deque(int size)
{
	Deque *tmp = (Deque *) malloc(sizeof(Deque));
	tmp->capacity = size;
	tmp->patient = (Patient *) malloc(sizeof(Patient) * tmp->capacity);
	tmp->head = tmp->tail = tmp->size = 0;
	return tmp;
}

void deque_delete(Deque **deque)
{
	for (int i = 0; i < (*deque)->size; i++)
		free((*deque)->patient[i].id);
	
	free((*deque)->patient);
	free(*deque);
}

int push_front(Deque *deque, Patient patient)
{
	if (deque->size == deque->capacity)
	{
		printf("Deque overflow!\n");
		return 1;
	}
		
	if (deque->size != 0)
	{
		if (deque->head == 0)
			deque->head = deque->capacity - 1;
		else 
			--deque->head;
	}

	deque->patient[deque->head] = patient;
	++deque->size;
} 

int pop_front(Deque *deque, Patient *patient)
{
	if (deque->size == 0)
		return 1;

	Patient a = deque->patient[deque->head];
	(*patient) = patient_input(a.id, a.ta, a.ts);

	free(a.id);

	//if (deque->head != deque->tail)
	if (deque->size != 1)
	{
		if (deque->head == deque->capacity - 1)
			deque->head = 0;
		else
			++deque->head;
	}
	--deque->size;
	
	return 0;
}

int push_back(Deque *deque, Patient patient)
{
	if (deque->size == deque->capacity)
	{
		printf("Deque overflow!\n");
		return 1;
	}

	if (deque->size != 0)
	{
		if (deque->tail == deque->capacity - 1)
			deque->tail = 0;
		else
			++deque->tail;
	}

	deque->patient[deque->tail] = patient;
	++deque->size;

	return 0;
}

int pop_back(Deque *deque, Patient *patient)
{
	if (deque->size == 0)
		return 1;

	Patient a = deque->patient[deque->tail];
	(*patient) = patient_input(a.id, a.ta, a.ts);

	free(a.id);
	
	//if (deque->head != deque->tail)
	if (deque->size != 1)
	{
		if (deque->tail == 0)
			deque->tail = deque->capacity - 1;
		else 
			--deque->tail;
	}

	--deque->size;

	return 0;
}

void deque_print(const Deque *deque)
{			
	for (int i = 0, j = deque->head; i < deque->size; j = (j + 1) % deque->capacity, i++)
		patient_print(deque->patient[j]);
	printf("\n");	
}

#endif
