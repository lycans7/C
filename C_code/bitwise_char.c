/*
 * bitwise_char.c
 *
 *  Created on: 01-Aug-2018
 *      Author: Parth shah
 */

/* C Program to demonstrate use of bitwise operators with char values */

#include<stdio.h>

int main() {

	 unsigned char a = 5, b = 9; // a = 5(00000101), b = 9(00001001)
	 printf("a = %d, b = %d\n", a, b);
	 printf("a&b = %d\n", a&b); // The result is 00000001
	 printf("a|b = %d\n", a|b);  // The result is 00001101
	 printf("a^b = %d\n", a^b); // The result is 00001100
	 printf("~a = %d\n", a = ~a);   // The result is 11111010
	 printf("b<<1 = %d\n", b<<1);  // The result is 00010010
	 printf("b>>1 = %d\n", b>>1);  // The result is 00000100


	//////////////////////practical very important storing value in characters and conversion //////////////////////
	char ch = 4;
	unsigned char val = 4;
	printf("\n Ch = %d \n", ch);
	printf("\n ~Ch = %d \n", ~ch);   //it will take 2's complement as answer .
	printf("\n Ch = ~ch = %d \n", ch = ~ch); //it will take 2's complement and store.

	printf("\n val = %d \n", val);
	printf("\n ~val = %d \n", ~val); // it will take 2's complement as answer.
	printf("\n val = ~val = %d \n", val = ~val); // it will take 1's complement and store in val.


	////////////////////remember that /////////////////////////////////////////////////////////
	// if you use logical operator ("&&") it gives answer in form of 1 and 0, if zero is     //
	// there in any side of the comparison then result will be zero otherwise 1, in any case //
	// even in negative number.                                                              //
	//                                                                                       //
	// and bitwise ("&") it gives answer in integer ,zero and negative integer ,             //
	// like 5 , -5 ,0 ,2 means answer respect of AND operation.                              //
	///////////////////////////////////////////////////////////////////////////////////////////

	printf("\n 0 && 5 = %d,\n 2 && 5 =  %d,\n -1 && 6 =  %d,\n 6 & 7= %d \n",0 && 5,2&&5,-1 && 6,6&7);
	return 0;
}

