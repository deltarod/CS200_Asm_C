#include<stdio.h>
#include <iostream>
#include <iomanip>

int main()
{
//variables to store integers    
int a;
int b;

printf("Please enter a number:\n");
//save first number as a
scanf("%d",&a);

int binA;

printf("Entered number in decimal notation: %d \n",a);
printf("Entered number in hexadecimal notation: 0x%x \n",a);
printf("Entered number in binary notation: %d \n",binA);

printf("\n");

printf("Please enter another number:\n");
//save second number as b
scanf("%d",&b);


int binB;
printf("Entered number in decimal notation: %d \n",b);
printf("Entered number in hexadecimal notation: 0x%x \n",b);
printf("Entered number in binary notation: %d \n",binB);

printf("\n");
printf("Bitwise Operations on Decimal Notation \n");

int abAND = a&b;
int abOR = a|b;
int abXOR = a^b;
int abNOTa = ~a;
int abNOTb = ~b;
int abSHL = a<<b;
int abSHR = a>>b;

printf("a & b = %d \n",abAND);
printf("a | b = %d \n",abOR);
printf("a ^ b = %d \n",abXOR);
printf("~a = %d \n",abNOTa);
printf("~b = %d \n",abNOTb);
printf("a << b = %d \n",abSHL);
printf("a >> b = %d \n",abSHR);

printf("\n");
printf("Bitwise Operations on Hexadecimal Notation \n");
printf("a & b = 0x%x \n",abAND);
printf("a | b = 0x%x \n",abOR);
printf("a ^ b = 0x%x \n",abXOR);
printf("~a = 0x%x \n",abNOTa);
printf("~b = 0x%x \n",abNOTb);
printf("a << b = 0x%x \n",abSHL);
printf("a >> b = 0x%x \n",abSHR);

//I wanted to use the code below to convert
//from decimal to binary but i kept getting odd
//errors
//The code works independantly and is from
//http://groups.engin.umd.umich.edu/CIS/course.des/cis400/cpp/binary.html
/*
void binary(int);

void main(void) {
    int number;

	cout << "Please enter a positive integer: ";
	cin >> number;
	if (number < 0) 
		cout << "That is not a positive integer.\n";
	else {
		cout << number << " converted to binary is: ";
		binary(number);
		cout << endl;
	}
}

void binary(int number) {
	int remainder;

	if(number <= 1) {
		cout << number;
		return;
	}

	remainder = number%2;
	binary(number >> 1);    
	cout << remainder;
}
*/
return 0;
}


