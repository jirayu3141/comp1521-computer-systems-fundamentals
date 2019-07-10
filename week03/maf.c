// COMP1521 19t2 ... lab 03: Make a Float
// maf.c: read in bit strings to build a float value
// Written by John Shepherd, August 2017
// Completed by Jirayu Sirivorawong z5125805 27 Jun 2019

#include <assert.h>
#include <err.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <math.h>

typedef uint32_t word; //word is 32 bits

typedef struct float32 {
	// define bit_fields for sign, exp and frac
	// obviously they need to be larger than 1-bit each
	// and may need to be defined in a different order
	unsigned int frac : 23,exp : 8, sign : 1;
} float32;

typedef struct double64 {
	// define bit_fields for sign, exp and frac
	// obviously they need to be larger than 1-bit each
	// and may need to be defined in a different order
	u_int64_t frac : 52, exp : 11, sign : 1;
} double64;
//add comment

typedef union bits32 {
	float fval;   // interpret the bits as a float
	word xval;    // interpret as a single 32-bit word
	float32 bits; // manipulate individual bits
} bits32;

void checkArgs (int, char **);
bits32 getBits (char *, char *, char *);
char *showBits (word, char *);
bool justBits (char *, int);
double bin_to_dec (char *frac);
void print_union (bits32 x);
void dectobi (word, char *);

int main (int argc, char **argv)
{
	bits32 u;
	char out[50] = {'0'};

	// here's a hint ...
	u.bits.sign = u.bits.exp = u.bits.frac = 0;

	// check command-line args (all strings of 0/1
	// kills program if args are bad
	checkArgs (argc, argv);

	// convert command-line args into components of
	// a float32 inside a bits32, and return the union
	u = getBits (argv[1], argv[2], argv[3]);

	printf ("bits : %s\n", showBits (u.xval, out));
	printf ("float: %0.10f\n", u.fval);

	return EXIT_SUCCESS;
}

// convert three bit-strings (already checked)
// into the components of a struct _float
bits32 getBits (char *sign, char *exp, char *frac)
{
	bits32 new;
	new.bits.sign = new.bits.exp = new.bits.frac = 0;
	// convert char *sign into a single bit in new.bits
	new.bits.sign = (*sign == '0') ? 0 : 1;
	// convert char *exp into an 8-bit value in new.bits
	new.bits.exp = (unsigned int) strtol(exp, NULL, 2);
	// convert char *frac into a 23-bit value in new.bits
	new.bits.frac = (unsigned int)strtol(frac, NULL, 2);
	return new;
}

// convert the 32-bit bit-string in val into
// a sequence of '0' and '1' characters in buf
// assume that buf has size > 32
// return a pointer to buf
char *showBits (word val, char *buf) {

	//set buf to 0 so it prints all 32 bits (+2 for space)
	for (int i = 0, j = 34; i < j; i++)
		buf[i] = '0';
	//convert from decimal to binary and put it in buffer
	dectobi(val, buf);
	return buf;
}

// checks command-line args
// need at least 3, and all must be strings of 0/1
// never returns if it finds a problem
void checkArgs (int argc, char **argv)
{
	if (argc < 3)
		errx (EX_USAGE, "usage: %s Sign Exp Frac", argv[0]);

	if (! justBits (argv[1], 1))
		errx (EX_DATAERR, "invalid Sign: %s", argv[1]);
	if (! justBits (argv[2], 8))
		errx (EX_DATAERR, "invalid Exp: %s",  argv[2]);
	if (! justBits (argv[3], 23))
		errx (EX_DATAERR, "invalid Frac: %s", argv[3]);
	return;
}

// check whether a string is all 0/1 and of a given length
bool justBits (char *str, int len)
{
	assert (len >= 0);
	if (strlen (str) != (size_t) len)
		return false;

	while (*str != '\0') {
		if (*str != '0' && *str != '1')
			return false;
		str++;
	}
	return true;
}

//converts from binary to decimal
double bin_to_dec (char *frac){
	double twos = 2, fracDecimal = 0; 
    for (int i = 0, len = strlen(frac); i < len; ++i) 
    { 
        fracDecimal += (frac[i] - '0') / twos; 
        twos *= 2.0; 
    } 
	return fracDecimal;
}
//convert decimal to binary and store in buff (for float)
void dectobi(word val, char *buf) 
{
	//index tracks putting bindary into buff (to account for 0 infront)
	//index2 tracks string length 
	static int index = 0, index2 = 0;
	
	if (val == 0) {
		index = (index2 < 32 ? (32-index2): 0);
		//add space
		buf[1] = ' ';
		buf[10] = ' ';
		//accoutn for index that writes on space 
		if (index == 2 || index == 9) index++;
		return;
	}
	//index2 tracks string lenghth
	index2++;
	dectobi(val/2, buf);
	//when index touches space, dont on it
	if (index == 1 || index == 10) index++;
	//put binary in array
	buf[index] = (val%2) + '0';
	index++;
}

//convert decimal to binary for double
void dectobi64(word val, char *buf) 
{
	//index tracks putting bindary into buff (to account for 0 infront)
	//index2 tracks string length 
	static int index = 0, index2 = 0;
	
	if (val == 0) {
		index = (index2 < 64 ? (64-index2): 0);
		//add space
		buf[1] = ' ';
		buf[10] = ' ';
		//accoutn for index that writes on space 
		if (index == 2 || index == 9) index++;
		return;
	}
	//index2 tracks string lenghth
	index2++;
	dectobi(val/2, buf);
	//when index touches space, dont on it
	if (index == 1 || index == 10) index++;
	//put binary in array
	buf[index] = (val%2) + '0';
	index++;
}