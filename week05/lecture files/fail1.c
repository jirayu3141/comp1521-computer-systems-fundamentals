#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
extern int errno;

int main(int argc, char *argv[])
{
   if (argc < 2) {
      fprintf(stderr, "Usage: %s File\n", argv[0]);
      exit(1);
   }

   int in;
   do {
      in = open(argv[1], O_RDONLY);
   } while (in > 0);

   if (in < 0) {
      fprintf(stderr, "Can't open %s (err:%d)\n", argv[1], errno);
      exit(errno);
   }

   close(in);
   return 0;
}
