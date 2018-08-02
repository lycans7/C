/*
 * bitwise_palindrome.c
 *
 *  Created on: 02-Aug-2018
 *      Author: Parth shah
 */

/* bit wise palindrome operation, check on from 32 bit and another for 1 bit increasing and decreasing order
 *  if any of the bit is not same it is called as not a palindrome
 *  100000000000001 10000000000000001  4byte is representation*/

#include <stdio.h>

int palindrome(unsigned int actual, int pos) {
	return (actual & (1 << pos - 1) ? 1 : 0);
}

int findPalindrome(unsigned int x) {
	int start = 1, end = 0;
	end = sizeof(int) * 8;
	while (start < end) {
		if (palindrome(x, start) != palindrome(x, end)) {
			return 0;
		}
		start++;
		end--;
	}

	return 1;
}

int main() {

	unsigned int val = 1 << 15 + 1 << 16, ret = 0;
	ret = findPalindrome(val);
	if (ret == 1)
		printf("\n True \n");
	else
		printf("\n False \n");


	val = 1 << 31 + 1;
	ret = findPalindrome(val);
	if (ret == 1)
		printf("\n True \n");
	else
		printf("\n False \n");


	val = 54;
	ret = findPalindrome(val);
	if (ret == 1)
		printf("\n True \n");
	else
		printf("\n False \n");


	val = 1 << 29 + 1 << 2;
	ret = findPalindrome(val);
	if (ret == 1)
		printf("\n True \n");
	else
		printf("\n False \n");

	return 0;
}

