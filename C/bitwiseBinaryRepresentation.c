/*
 * bitwiseBinaryRepresentation.c
 *
 *  Created on: 02-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void binaryIterative(unsigned int x) {
	int i = 0;
	printf("\n");
	for (i = 31; i >= 0; i--) {
		(x & (1 << i)) ? printf("1") : printf("0");
	}
	printf("\n");
}

void binaryRecursive(unsigned int n) {
	if (n > 1)
		binaryRecursive(n / 2);
	printf("%d", n % 2);
}

int main() {

	int x;
	printf("\n Enter the number \n");
	scanf("%d", &x);
	binaryIterative(x);
	binaryRecursive(x);
	printf("\n");
	return 0;
}

