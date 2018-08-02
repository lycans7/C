/*
 * bitwiseSetBit1.c
 *
 *  Created on: 02-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int checkPowerOf2(unsigned int v) {
	return (v && (!(v & (v - 1))));
}

unsigned int Log2n(unsigned int n)
{
	if (!checkPowerOf2(n)) {
		printf("\n ERROR!!:: %d Invalid number \n", n);
		return -1;
	}
   return (n > 1)? 1 + Log2n(n/2): 0;
}

void checkBitposition(unsigned int v) {

	if (!checkPowerOf2(v)) {
		printf("\n ERROR!!:: %d Invalid number \n", v);
		return;
	}
	int count = 0;
	while (v) {
		v = v >> 1;
		count++;
	}
	printf("\n Set bit at %d position \n", count);
}

int main() {
	unsigned int val,i;
	printf("\n Enter the value to check position of set bit \n");
	printf("\t");
	scanf("%d", &val);
	checkBitposition(val);
	i = Log2n(val);
	printf("\n Set bit at %d position \n", i + 1);
	return 0;
}

