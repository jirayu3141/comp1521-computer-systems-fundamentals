// sadd2.c ... add a student record via write()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   int stufd = open("Students2",O_WRONLY|O_CREAT|O_APPEND,0644);
   if (stufd < 0) {
      perror("Can't open student data");
      exit(errno);
   }
   
   Student stude;
   if (getStudentData(&stude) < 0) {
      perror("Invalid student data");
      exit(1);
   }
   showStudentData(stude);

   ssize_t nbytes;
   nbytes = write(stufd, &stude, sizeof(Student));
   if (nbytes < 0) {
      perror("Write failed");
      exit(errno);
   }
   if (nbytes != sizeof(Student)) {
      char msg[50];
      sprintf(msg, "Only wrote %d", (int)nbytes);
      perror(msg);
      exit(errno);
   }
   close(stufd);

   return 0;
}
