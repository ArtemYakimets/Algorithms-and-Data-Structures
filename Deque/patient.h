#ifndef PATIENT_H
#define PATIENT_H

typedef struct Patient {
	char *id;
	int ta;
	int ts;
} Patient;

Patient patient_input(char *, int, int);
void patient_print(const Patient);
char *patient_delete_asterisk(char *);

#endif
