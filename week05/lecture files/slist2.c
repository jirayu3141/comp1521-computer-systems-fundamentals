// slist2.c ... list student records via scanf()

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   FILE *stuf = fopen("Students2","r");
   if (stuf == NULL)
      error(errno, errno, "Can't open student data");

   Student stude;  char line[100];
   while (fgets(line,100,stuf) != NULL) {
      sscanf(line, "%d:%[^:]:%[^:]:%d:%f",
         &stude.id, &stude.given[0], &stude.family[0], &stude.prog, &stude.wam);
      showStudentData(stude);
   }

   fclose(stuf);
   return 0;
}
