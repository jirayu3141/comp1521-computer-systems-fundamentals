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
    bn->bytes = calloc(Nbytes , sizeof(Byte));
    assert(bn->bytes != NULL);
    return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum bnA, BigNum bnB, BigNum *res) {
    // TODO
    
    //adding last digit and track the carry
    int sum = 0, carry = 0, currA = 0, currB = 0, ind = 0;
    while (bnA.bytes[currA] || bnB.bytes[currB] != '\0') {
        if (ind >= 20) {
            res->bytes = realloc (res->bytes, (ind+1) * sizeof(Byte));
        }
        int A = 0, B = 0;
        /*convert char to int*/
        if (bnA.bytes[currA] != '\0')
            A = bnA.bytes[currA] - '0';
        else
            A = 0;
        if (bnB.bytes[currB] != '\0') 
            B = bnB.bytes[currA] - '0';
        else
            B = 0;
        

        /*do the addition*/
        sum = A + B;
        /*check if it has exsisitng carry */
        if (carry == 1) {
            sum++;
            carry = 0;
        }
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        }
        printf("A is %i\n", A);
        printf("B is %i\n", B);
        printf("carry is %i\n", carry);
        printf("sum is %c\n", (Byte)(sum) + '0');
        res->bytes[ind] = (Byte)sum + '0';

        if (bnA.bytes[currA] != '\0') 
            currA++;
        if (bnB.bytes[currB] != '\0') 
            currB++; 
        ind++;
        /*check of there are still carry*/
        if (carry == 1) {
            res->bytes[ind+1] = '1';
        }
        /*reallocate size for res if it is above 20 digis */
        
        res->nbytes = ind-1;
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
    int flag_non_zero = 0;
    /* search for number and scan in order */
    while (*curr != '\0') {
        if (isdigit(*curr)) {
            if (num >= 20) {
                bn->bytes = realloc (bn->bytes, num * sizeof(Byte));
            }
            flag = 1;   //digit is found
            if (*curr != '0') {
                flag_non_zero = 1;
            }
            if (flag_non_zero == 1) {            
                bn->bytes[num] = *curr;
                num++;
            }
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
    bn->nbytes = num-1;

    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum bn) {
    
    //printing backwards
    for (int start = 0, end = bn.nbytes; end >= start; end--) {
        printf("%c", bn.bytes[end]);
    }
}
