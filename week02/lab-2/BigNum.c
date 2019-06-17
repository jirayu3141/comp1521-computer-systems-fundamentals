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
    // if it is not digit, return 0
    Byte *curr = bn->bytes;
    unsigned char flag = 0;
    while (*s != '\0') {
        if (isnumber(*s)) {
            flag = 1;
            *curr = *s;
            curr++;
        }
        s++;
    }
    *curr = '\0';
    if (flag == 0) return 0;
    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum bn) {
    // TODO
    printf("%s", bn.bytes);
    return;
}
