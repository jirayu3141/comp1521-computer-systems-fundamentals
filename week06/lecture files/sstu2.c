// sstu2.c ... show the i'th student

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(int argc, char *argv[])
{
   if (argc < 2) {
      fprintf(stderr,"Usage: %s N\n", argv[0]);
      exit(1);
   }
   int i;
   if (sscanf(argv[1], "%d", &i) < 1) {
      fprintf(stderr,"Usage: %s N\n", argv[0]);
      exit(1);
   }

   int stufd = open("Students2",O_RDONLY);
   if (stufd < 0) {
      perror("Can't open student data");
      exit(errno);
   }
   int status = lseek(stufd, i*sizeof(Student), SEEK_SET);
   if (status < 0) {
      fprintf(stderr, "Can't seek to %d'th\n", i);
      exit(errno);
   }
   Student stude;
   int nbytes = read(stufd, &stude, sizeof(Student));
   if (nbytes < sizeof(Student)) {
      fprintf(stderr, "Can't read %d'th\n", i);
      exit(errno);
   }
   showStudentData(stude);

   close(stufd);
   return 0;
}
