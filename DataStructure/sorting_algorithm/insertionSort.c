/*
 * insertionSort.c
 *
 *  Created on: 16-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void PS_insertionSort(int* ins, int size) {

	int i, val, block;
	for (i = 0; i < size; i++) {
		val = ins[i]; //saving current value to temporary variable;
		block = i;
		while (block > 0 && ins[block - 1] > val) {
			ins[block] = ins[block - 1]; //suppose you are at 4 position, saving 3 value to 4 position , 2 to 3 pos...
			block = block - 1;
		}
		ins[block] = val; //saving 4 to 1 example consider from up print.
	}
}

int main() {
	int sort[] = { 7, 2, 4, 1, 5, 3 }, i, size;

	size = sizeof(sort) / sizeof(sort[0]);
	printf(" \n ");
	for (i = 0; i < size; i++)
		printf(" %d ", sort[i]);
	printf(" \n ");
	PS_insertionSort(sort, size);
	for (i = 0; i < size; i++)
		printf(" %d ", sort[i]);
	printf(" \n ");
	return 0;
}

