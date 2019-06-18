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
    //adding last digit and track the carry
    int sum = 0, carry = 0, currA = 0, currB = 0;
    while (bnA.bytes[currA] && bnB.bytes[currB] != '\0') {
        int A = atoi (bnA.bytes[currA]);
        int B = atoi (bnB.bytes[currB]);
        if (carry == 1) {
            sum++;
            carry = 0;
        }
        sum = A + B;
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        }
        res->bytes 
        res->nbytes++;


        if (bnA.bytes[currA] != '\0') currA++;
        if (bnB.bytes[currB] != '\0') currB++; 
    }

    return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *bn) {
    // check if the string contain numbers and how many digits there are
    int flag = 0; //flag if number is detected
    char *curr = s;
    int num = 0; //int to store the number of digits
    
    /* search for number and scan in order */
    while (*curr != '\0') {
        if (isdigit(*curr)) {
            flag = 1;   //digit is found
            bn->bytes[num] = *curr;
            num++;
        }
        curr++;
    }
    if (flag == 0) return 0;
	
    /*reverse the array*/
    int start = 0;
    int end = num-1;
    Byte tmp;
    while (start < end) {
        tmp = bn->bytes[start];
        bn->bytes[start] = bn->bytes[end];
        bn->bytes[end] = tmp;
        start++;
        end--;

    }


    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum bn) {
    // TODO
    //printing backwards
    for (int start = 0, end = bn.nbytes; end >= start; end--) {
        printf("%c", bn.bytes[end]);
    }
}
