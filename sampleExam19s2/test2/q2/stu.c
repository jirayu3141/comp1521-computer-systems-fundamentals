// stu.c ... manipulate student records

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "Students.h"

int main (int argc, char *argv[])
{
	if (argc < 2) {
		fprintf (stderr, "Usage: %s StuFile\n", argv[0]);
		return 1;
	}

	// attempt to open named file
	int fd; // input file descriptor
	if ((fd = open (argv[1], O_RDONLY)) < 0) {
		fprintf (stderr, "Can't open %s\n", argv[1]);
		return 1;
	}

	// fetch student records
	Students ss = getStudents (fd);
	if (ss == NULL) {
		fprintf (stderr, "Can't set up student records\n");
		return 1;
	}

	// display student records
	//showStudents (ss);

	return 0;
}
