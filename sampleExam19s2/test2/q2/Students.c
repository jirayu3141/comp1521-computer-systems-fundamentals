// Students.c ... implementation of Students datatype

#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Students.h"

typedef struct sturec sturec;
typedef struct students students;

struct sturec {
	int id;
	char name[20];
	int degree;
	float wam;
};

struct students {
	int nstu;
	StuRec recs;
};

// build a collection of student records from a file descriptor
Students getStudents (int in)
{
	struct sturec *new = malloc(sizeof(*new));

	while (read(in, new, sizeof(*new)) > 0)
		showStuRec(new);

	printf("end of func");
	return NULL; // TODO ... replace this by your code
}

// show a list of student records pointed to by ss
void showStudents (Students ss)
{
	if (ss == NULL)
		printf ("NULL\n");
	else if (ss->nstu == 0)
		printf ("<no students>\n");
	else
		for (int i = 0; i < ss->nstu; i++)
			showStuRec (&(ss->recs[i]));
}

// show one student record pointed to by s
void showStuRec (StuRec s)
{
	printf ("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}
