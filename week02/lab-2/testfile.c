#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigNum.h"

int main (int argc, char *argv[]) {
    BigNum num1; // first input number
	BigNum num2; // second input number
	BigNum sum;  // num1 + num2

    // Initialise BigNum objects
	initBigNum (&num1, 20);
	initBigNum (&num2, 20);
	initBigNum (&sum, 20);

    scanBigNum(argv[1], &num1);
    //scanBigNum(argv[2], &num2);
    return 0;
}