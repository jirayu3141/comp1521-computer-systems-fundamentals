#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main(int argc, char *argv[])
{
   if (argc < 2) 
      error(1, 0, "Usage: %s File", argv[0]);

   int in;

   do {
      in = open(argv[1], O_RDONLY);
   } while (in > 0);

   if (in < 0)
      error(errno, errno, "Can't open %s", argv[1]);

   close(in);
   return 0;
}

