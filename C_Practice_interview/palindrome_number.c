/*
 * palindrome_number.c
 *
 *  Created on: 11-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main() {

	int val, buff, len, rem;
	printf("\n Enter the number for palindrome \n");
	scanf("%d", &val);
	len = val;
	while (val > 0) {
		rem = val % 10;
		buff = buff * 10 + rem;
		val /= 10;
	}
	if (buff == len) {
		printf("\n palindrome  number %d = %d \n", len, buff);
	} else {
		printf("\n not palindrome  number %d = %d \n", len, buff);
	}
}

