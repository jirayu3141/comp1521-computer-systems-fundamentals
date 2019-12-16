// sstu1.c ... show the i'th student

#include <stdio.h>
#include <stdlib.h>
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

   FILE *stuf = fopen("Students1","r");
   if (stuf == NULL) {
      perror("Can't open student data");
      exit(errno);
   }
   int counter = 0;  char line[100];
   while (1) {
      if (fgets(line,100,stuf) == NULL) {
         counter = -1;
         break;
      }
      if (counter == i) break;
      counter++;
   }
   if (counter == -1) {
      fprintf(stderr, "Can't find student #%d\n", i);
      exit(1);
   }
   else {
      Student stude;
      sscanf(line, "%d:%[^:]:%[^:]:%d:%f",
             &stude.id, &stude.given[0], &stude.family[0], &stude.prog, &stude.wam);
      showStudentData(stude);
   }
   fclose(stuf);
   return 0;
}
