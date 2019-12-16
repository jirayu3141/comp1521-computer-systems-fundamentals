#include <stdio.h>

int main(int argc, char **argv)
{
   FILE *in;  int ch;  int n = 1;

   while (1) {
      if ((in = fopen("abc", "r")) == NULL)
         break;
      printf("Copy #%d\n", n++);
      while ((ch = fgetc(in)) != EOF)
         putc(ch, stdout);
      fclose(in);
   } 
   return 0;
}
