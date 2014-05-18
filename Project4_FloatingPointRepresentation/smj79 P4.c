//This program accepts a floating point number and displays a bit-level representation of the number. 

//headers to import libraries
#include <conio.h> //Non-standard header file to provide console input/output
#include <math.h> //C Standard Math Library
#include <stdio.h> //C library to perform Input/Output operations
#include <stdlib.h> //C Standard General Utilities Library
#include <string.h> //C library for performing manipulating C strings and arrays.


void float2bin(int input, int bits, char* binRep);

/*Binary representation: Takes in int and outputs string.
Used by the main method to perform ops on the binary rep*/
void float2bin(int input, int bits, char* binRep)
{
    int i;//pointer
	//array of characters for binary rep
    binRep[bits] = '\0';
	//for the number of bits 
    for (i = bits - 1; i >= 0; --i, input >>= 1)
    {
		//add in bit to array
        binRep[i] = (input & 1) + '0';
    }
}

int main(void) {

	/*String arrays for storing binary representation.
	8 bits for exponent, 23 for mantissa and 32 for the binary rep.*/  
	char exponentArr[8], mantissaArr[23], binRep[32];
	
	//Int arrays for breaking up and storing the exponent, sign and significand
	int exponentInt, signInt, signifInt = 0; 
	
	//float variable to store input
	float f;
	
	//prompt user for float
	printf("Enter real number: "); 
	
	//accept float as input
	scanf("%f", &f);

	/*Get the address of the float, cast it to an int
	http://stackoverflow.com/questions/12868444/convert-float-to-binary-in-c */
 	int f2Bin = *((int*)&f);

	printf("\n"); //blank line 

	//header
	printf("Float Analysis: \n");

	//BINARY REPRESENATION

	//convert float to 32-bit binary
 	float2bin(f2Bin, 32, binRep); 

	/*Decimal to binary
	http://stackoverflow.com/questions/10682634/convert-decimal-to-32-bit-binary*/
	printf("  Bit Pattern: ");
 	for (int pos = 0; pos < 32; pos++){
		//print binary rep	
		printf("%c", binRep[pos]); 
		if (pos==0 || pos == 8)
			//space to break up sign and exponent
			printf(" "); 
	}

	//To label the broken up binary representation as defined in the guide
	printf("\n\t       S Exponent Significand/Mantissa");

	printf("\n"); //blank line
	printf("\n"); //blank line 

	//SIGN

	//right-bit shift to "scoot" to the sign
 	signInt = (f2Bin >> 31); 

	//if the leading number is 0
	if(signInt == 0){ 
		//positive number
		printf("  Sign:	   0 (positive) \n");
	}else{
		//negative number
		printf("  Sign:	   1 (negative) \n");
	}
 	
	//EXPONENT
	/*http://stackoverflow.com/questions/15685181/how-to-get-the-sign-
	mantissa-and-exponent-of-a-floating-point-number*/

	//exponent mask
	int expMask = 255; 

	//right-bit shift to "scoot" to the exponent
	signifInt = (f2Bin>>23) & expMask;
	
	//exponent mask (zeroes out the mantissa and sign)
 	exponentInt = (signifInt) & 0xff; 

 	//binary rep for the exponent
 	float2bin(exponentInt,8, exponentArr);

	printf("  Exponent:	  ");
 	printf(exponentArr); 

	//32-bit binary has a bias of 127 
	int exponent = signifInt - 127; 

	//without bias
	printf("= %i; w/ bias 127 -> (%i - 127) = %i \n", signifInt, signifInt, exponent); 

	//SIGNIFICAND

	//binary rep for the significand
 	float2bin(f2Bin, 23, mantissaArr);
	printf("  Significand:    ");
 	printf(mantissaArr);
	printf("\n");
	printf("    w/impilied 1: 1.");
	printf(mantissaArr); 
 	printf("\n"); //blank line

	//ALTERNATE REPRESENTATION

	//tests for 1's
	int test = 1; 
	//exponent init
	int expInit = 0; 
	printf("\n  Combined:	  + [1");
	//iterate through mantissa
	for(int index = 1; index <23; index++){
		int x = 0; 
		//right-shift to test bit for 1's
		x = f2Bin >> (23 - index); 
		x = x & test;
		//exponent is initialized for the bit
		expInit = pow(2, index); 
		//if there is a 1
		if(x == 1){ 
			//print the term as a fraction
			//keeps going and prints a summation of terms
			printf("+ (1/%i) ", expInit); 
		}
	}
	printf("] * 2^(%i)\n", exponent); 

	//non-fractional representation
 	printf("    or:	    + [1.");
	printf(mantissaArr);
	printf("] * 2^(%i)\n", exponent); 
	

 	
}
