// cat3.c ... copy file to stdout

#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main(int argc, char *argv[])
{
   // process args and set up for read
   if (argc < 2) 
      error(1, 0, "Usage: %s File", argv[0]);
   int in = open(argv[1], O_RDONLY);
   if (in < 0)
      error(errno, errno, "Can't open %s", argv[1]);

   // read block-by-block

   ...

   // release resources
   close(in);
   return 0;
}

