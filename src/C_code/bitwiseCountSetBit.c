/*
 * bitwiseCountSetBit.c
 *
 *  Created on: 02-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void countBit(unsigned int v) {
	int i = 0, count = 0;
	printf("\n");
	while (v) {
		for (i = 31; i >= 0; i--) {
			if (v & (1 << i)) {
				count++;
			}
		}
		v--;
	}
	printf("\n %d \n", count);
}

int main() {
	unsigned int val;
	printf("\n Enter the number \n");
	scanf("%d", &val);
	countBit(val);
	return 0;
}

