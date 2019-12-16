// Attempt to open a file

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
extern int errno;

int main(int argc, char *argv[])
{
   int in;
   if (argc < 2) {
      fprintf(stderr, "Usage: %s File\n", argv[0]);
      exit(1);
   }
   in = open(argv[1],O_RDONLY);
   if (in < 0) {
      fprintf(stderr, "Can't open %s: ", argv[1]);
      perror(NULL);
      exit(errno);
   }
   else {
      printf("Opened %s\n", argv[1]);
   }
   close(in);
   return 0;
}
