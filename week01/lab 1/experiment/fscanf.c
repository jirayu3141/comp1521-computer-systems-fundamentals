#include <stdio.h>
int main()
{
   FILE* ptr = fopen("abc.txt", "r");
   if (ptr == NULL)
   {
      printf("no such file\n");
   }

   char* buf[100];

while(fscanf(ptr, "%s", buf) == 1)
{
   if (*buf == '\n')
   {
      printf("\n");
   }

   printf("%s", buf);

}
   return 0;
}
