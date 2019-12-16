// slist2.c ... show all student records via read()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   int stufd = open("Students2",O_RDONLY);
   if (stufd < 0) {
      perror("Can't open student data");
      exit(errno);
   }

   Student stude;
   while (read(stufd, &stude, sizeof(Student)) > 0)
      showStudentData(stude);

   close(stufd);
   return 0;
}
