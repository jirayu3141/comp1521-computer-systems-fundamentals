// BigNum.c ... LARGE positive integer values

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigNum.h"

// Initialise a BigNum to N bytes, all zero
void initBigNum(BigNum *bn, int Nbytes) {
    // TODO
    bn->nbytes = Nbytes;
    bn->bytes = malloc(Nbytes * sizeof(Byte));
    assert(bn->bytes != NULL);
    return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum bnA, BigNum bnB, BigNum *res) {
    // TODO
    return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *bn) {
    // check if the string contain numbers and how many digits there are
    int flag = 0;
    char *curr = s;
    while (*curr != '\0') {
        if (isdigit(*curr)) {
            bn->nbytes++;
            flag = 1;
            curr++;
        }
    }
    if (flag == 0) return 0;
	//scan in backwards
    sscanf((char *)(bn->bytes), s);

    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum bn) {
    // TODO
    // read numbers backwards, by scanning to the last point of arrray then read
    // it
    int start = 0;
    // need to -3 beacuse of '\0', array start with 0 and the sign bit
    int end = strlen((char *)bn.bytes) - 3;
    while (end >= start) {
        printf("%c", bn.bytes[end]);
        end--;
    }
}
