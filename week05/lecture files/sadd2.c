// sadd2.c ... add a student record via printf()

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   FILE *stuf = fopen("Students2","a");
   if (stuf == NULL)
      error(errno, errno, "Can't open student data");

   Student stude;
   if (getStudentData(&stude) < 0)
      error(1, 0, "Invalid student data");
   showStudentData(stude);

   fprintf(stuf, "%d:%s:%s:%d:%f\n",
      stude.id, stude.given, stude.family, stude.prog, stude.wam);
   fclose(stuf);

   return 0;
}
