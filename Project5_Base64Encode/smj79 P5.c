/*This program accepts a string and outputs its Base64 encoding.
Reference:
http://www.thedbcommunity.com/index.php?option=com_content&task=view&id=244&Itemid=56*/

//headers to import libraries
#include <conio.h> //Non-standard header file to provide console input/output
#include <math.h> //C Standard Math Library
#include <stdio.h> //C library to perform Input/Output operations
#include <stdlib.h> //C Standard General Utilities Library
#include <string.h> //C library for performing manipulating C strings and arrays.

//method takes in input and returns a binary representation
void float2bin(int input, int bits, char* binRep);
//method converts a byte set of 3 characters to an array of 4 6-bit integers
void encode64(char* src, int dest[5]);

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

/*Encoding to Base64: Every 3 original characters are transformed 
into 4 6-bit integers using bitwise operations
In the comments I have shown what happens to a byte set of
155, 162 and 233

I used the following link for reference:
http://www.thedbcommunity.com/index.php?option=com_content&task=view&id=244&Itemid=56*/
void encode64(char* src, int dest[5]) {

	//three byte sets 
	char ch0 = src[0]; //ex. 155
	char ch1 = src[1]; //ex. 162
	char ch2 = src[2]; //ex. 233

	//four 6-bit integers
	//Use first 6 bits of first character
	int in0 = ch0 >> 2; //38 (in binary: 100110) 
	//Use last 2 bits of first character + first 4 bits of second character
	int in1 = (((ch0&3)<<4)+((ch1&240)>>4)); //58 (in binary: 111010)
	//Use last 4 bits of second character + first 2 bits of third character
	int in2 = ((ch1 << 2)+(ch2>>6))&63; //11 (in binary: 001011)
	//Use last 6 bits of third character
	int in3 = ch2&63; //41 (in binary: 101001)

	//integer array to hold the 6-bit conversions
	dest[0] = in0; //38
	dest[1] = in1; //58
	dest[2] = in2; //11
	dest[3] = in3; //41

}

int main(void) {
	//ARRAYS
	//input array
	char str[80];
	//table for encoding to Base64
	char base64EncodingTable[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//Base64 output array
	char output[120];

	//GET STRING
	//prompt user for string
	printf("Please enter a string to convert: ");
	//accept string as input
	scanf("%s", &str);
	//display entered string
	printf("Original Data: %s. \n\n", str);
	//capture length of string
	int str_len = strlen(str);

	//STRING TO ASCII
	//display ASCII
	printf("ASCII codes :- ");
	for(int i = 0; i<str_len; i++){
		printf("%c: %d ", str[i], str[i]);
	}
	printf("\n\n");

	//ASCII TO BINARY
	//array to hold binary rep
	char toBin[8];
	printf("Groups of 8: ");
	/*iterates through the input string and converts to
	binary rep*/
	for(int i = 0; i<str_len; i++){
		float2bin(str[i], 8, toBin);
		printf(toBin);
		//space between binary reps
		printf(" ");
	}

	//DIVIDING INTO 3 BYTE SETS
	//Divide the string into 3 byte sets
	int setsOfThree = str_len/3;
	//Character array of 3 byte sets
	char byteSet[3];
	//6-bit arrays
	int sixBitsArray[5];
	//an array of all the bits
	int bitOutputArray[120];
	//number of 4 6-bit sets
	int sixBitSets = 0;

	//iterates through the 3 byte sets
	for(int i = 0; i < setsOfThree; i++){
		//divides the string up into byte sets of three
		byteSet[0] = str[i*3];
		byteSet[1] = str[(i*3)+1];
		byteSet[2] = str[(i*3)+2];
		
		//encode64 takes in the byte sets and returns an array of 4 6-bit integers
		encode64(byteSet, sixBitsArray);

		//an overall array composed of the 4 6-bit integer arrays
		bitOutputArray[i*4] = sixBitsArray[0];
		bitOutputArray[(i*4)+1] = sixBitsArray[1];
		bitOutputArray[(i*4)+2] = sixBitsArray[2];
		bitOutputArray[(i*4)+3] = sixBitsArray[3];
		//number of 4 6-bit sets
		sixBitSets += 4;
	}

	//LEFTOVERS
	//characters that don't fit into the groups of 3
	int leftOver = str_len%3;
	//for equals signs
	int padding = 0;

	//if just one byte left
	if(leftOver == 1){
		//get the character
		char lastCharacter = str[str_len-1];
		//convert character to Base64
		char shiftBase64 = (lastCharacter>>2)&63;
		char lastBase64 = ((lastCharacter&3)<<4)&63;
		//add to output array
		bitOutputArray[sixBitSets++] = shiftBase64;
		bitOutputArray[sixBitSets++] = lastBase64;
		//The '==' sequence indicates that the last group contained only one byte
		padding = 2;

	//if just two bytes left
	} else if(leftOver == 2) {
		//get the character
		char lastCharacter = str[str_len-1];
		//get the second to last character
		char secondLast = str[str_len-2];
		//convert character to Base64
		char shiftSecondLast = (secondLast>>2)&63;
		char shiftedBase64 = (((secondLast&3)<<4)+((lastCharacter&240)>>4));
		char lastBase64 = (lastCharacter&15)<<2;
		//add to output array
		bitOutputArray[sixBitSets++] = shiftSecondLast;
		bitOutputArray[sixBitSets++] = shiftedBase64;
		bitOutputArray[sixBitSets++] = lastBase64;	
		//The '=' sequence indicates that the last group contained two bytes
		padding = 1;
	}

	//GROUPS OF 6
	printf("\n\n");
	char setsOfSix[8];
	printf("Groups of six: ");
	//iterate through Base64s
	for(int i = 0; i < sixBitSets; i++){
		//Convert to Binary every 6
		float2bin(bitOutputArray[i], 8, setsOfSix);
		for(int j = 2; j <= 8; j++){
			printf("%c", setsOfSix[j]);
		} 
	}

	//BASE 10
	printf("\n\n");
	printf("In base 10: ");
	//iterate through Base64s
	for (int i = 0; i<sixBitSets; i++){
		//print decimal value
		printf("%i ", bitOutputArray[i]);
	}

	//BASE64
	printf("\n\n");
	printf("In base64: ");
	//iterate through Base64s
	for(int i = 0; i<sixBitSets; i++) {
		//add to output array from table
		output[i] = base64EncodingTable[bitOutputArray[i]];
	}
	//print base64 values
	printf(output);

	/*		
	Add Padding
	The '=' sequence indicates that the last group contained two bytes
	The '==' sequence indicates that the last group contained only one byte*/
	if(padding>0){
		for(int i = 1; i < padding+1; i++){
			printf("=");
		}
	}
	printf("\n");
	return 0;	
}





