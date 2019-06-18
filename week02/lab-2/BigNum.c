// BigNum.c ... LARGE positive integer values

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BigNum.h"


// Returns the number of real digits from strings
int real_digits (char *s) {
    int size = 0;
    for (int i = 0, j = strlen(s), found_num = 0; i<j; i++) {
       //check for the index of the first real number
       if (s[i] >= '1' && s[i]<= '9' && found_num != 1) {
           found_num = 1;
       }
       //count the size of digits
        if (found_num > 0 && isdigit(s[i])) {
            size++;
        }
    }
    return size;
}

//put real digits into array, array of digit-rich
char *digits_to_array(char *s) {
    int size = real_digits(s);
    //allocate space for the array
    char *digits = malloc(sizeof(Byte) * size);

    for (int i = 0, j = strlen(s), found_num = 0, ind = 0; i<j; i++) {
       //check for the index of the first real number
       if (s[i] >= '1' && s[i]<= '9' && found_num != 1) {
           found_num = 1;
       }
       //pass in the digits to array
        if (found_num > 0 && isdigit(s[i])) {
            digits[ind] = s[i];
            ind++;
        }
    }
   
    return digits;
}

void reverse_string (char *s) {
    int tmp = 0;
    for (int start = 0, end = strlen(s) - 1; start < end; start++,end--) {
        tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
    }
}

bool checkvalid(char *s) {
    int flag = 0;
    for (int i = 0, j = strlen(s); i < j; i++) {
        if (isdigit(s[i])) {
            flag = 1;
        }
    }
    if (flag ==0) return false;
    else return true;
}

void copy_string (Byte *dest, char *source) {
    for (int i = 0, j = strlen(source); i < j; i++) {
        dest[i] = source[i];
    }
}

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
    int i = 0, j = 0,sum = 0, carry = 0;
    char tmp[100] = {'\0'};
    res->nbytes = 0;
    while (bnA.bytes[i] != '\0' || bnB.bytes[j] != '\0') {
        int A = bnA.bytes[i] != '\0' ? bnA.bytes[i] - '0' : 0;
        int B = bnB.bytes[j] != '\0' ? bnB.bytes[j] - '0' : 0;
        //calculate value of the digits
        sum = carry + A + B;
        /* debug */
        //printf("this is : %i\n", A);
        //update the carry
        carry = (sum >= 10) ? 1 : 0;
        //update sum if greater than 10
        sum = sum % 10;
        //put sum into the array
        tmp[i >= j ? i : j] = sum + '0';
        //update the size of sum
        res->nbytes++;
        //move to the next digit
        if (bnA.bytes[i] != '\0') i++;
        if (bnB.bytes[j] != '\0') j++;
    }
    if (carry > 0) {
        tmp[res->nbytes] = '1';
        res->nbytes++;
    }
    if (res->nbytes > 20) {
        res->bytes = realloc(res->bytes, sizeof(Byte) * strlen(tmp));
    }
    copy_string(res->bytes, tmp);


    return;
}



// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *bn) {
    /*check if it exceed previously allocated space*/
    int size = real_digits(s);
    if (size > 20) {
         bn->bytes = realloc(bn->bytes, size * sizeof(Byte));
    }
    if (!checkvalid(s)) return 0;
    char* digits = digits_to_array(s);
    reverse_string(digits);
    bn->bytes = (Byte *)strcpy((char *)bn->bytes, digits);
    bn->nbytes = size;

    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum bn) {
    
    //printing backwards
    for (int start = 0, end = bn.nbytes - 1; end >= start; end--) {
        printf("%c", bn.bytes[end]);
    }
}
