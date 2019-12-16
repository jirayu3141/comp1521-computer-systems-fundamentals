// sadd1.c ... add a student record via printf()

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   FILE *stuf = fopen("Students1","a");
   if (stuf == NULL) {
      perror("Can't open student data");
      exit(errno);
   }

   Student stude;
   if (getStudentData(&stude) < 0) {
      perror("Invalid student data");
      exit(1);
   }
   showStudentData(stude);

   fprintf(stuf, "%d:%s:%s:%d:%f\n",
      stude.id, stude.given, stude.family, stude.prog, stude.wam);
   fclose(stuf);

   return 0;
}
