/*
 * bitwiseCountSetAndUnsetBit.c
 *
 *  Created on: 03-Aug-2018
 *      Author: Parth shah
 */

/**************************** check 1010 = 2(1),2(0) **********************/
#include <stdio.h>

void checkBit(unsigned int val) {
	int zeros = 0, once = 0;
	while (val) {
		if (val & 1)
			once++;
		else
			zeros++;
		val = val >> 1;
	}
	printf("\n zero = %d, one = %d \n", zeros, once);
}

int main() {
	unsigned int bit_check;
	printf("\n Enter the number to check equal number of bit or not \n");
	scanf("%d", &bit_check);
	checkBit(bit_check);
	int p = 14,c = 13;
	printf("%d ",p & ~(p-1));
	printf("%d ",~(p-1));
	printf("%d ",~p);
	printf("%d ",~c);
	return 0;
}
