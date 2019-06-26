// COMP1521 19t2 ... lab 03: where are the bits?
// watb.c: determine bit-field order

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
	unsigned int a : 4;
	unsigned int b : 8;
	unsigned int c : 20;
};


int main (void)
{
	struct _bit_fields x;
        x.a = 0b1111;
        x.b = 0b0;
        x.c = 0b10101010101010101010;

        unsigned int *ptr = (unsigned int *)&x;
        unsigned int mask = (1 << 31);

        for (int i = 0; i < 32; i++) {
            int y = (*ptr & mask) > 1 ? 1 : 0;
            printf("%i", y);
            mask = (mask >> 1);
        }

        printf ("\n%zu\n", sizeof (x));

        return EXIT_SUCCESS;
}
