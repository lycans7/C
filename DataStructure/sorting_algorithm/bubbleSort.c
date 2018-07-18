/*
 * bubbleSort.c
 *
 *  Created on: 16-Jul-2018
 *      Author: Parth shah
 */

/******************* In each iteration interchanging the value ****************
 ********************in the last minimum value at left side and max at right**/

#include <stdio.h>

void PS_bubbleSort(int* bub, int size);
void PS_swap(int* first, int* second);

int main() {
	int sort[] = { 100, 50, 2, 30, 45, 89, 70 }, len, i;
	len = sizeof(sort) / sizeof(sort[0]);
	for (i = 0; i < len; i++)
		printf(" %d ", sort[i]);
	printf("\n %d \n", len);
	PS_bubbleSort(sort, len);
	for (i = 0; i < len; i++)
		printf(" %d ", sort[i]);
	printf(" \n ");
	return 0;
}

void PS_bubbleSort(int* bub, int size) {
	int i, j, flag, count = 0;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1; j++) {
			if (bub[j] > bub[j + 1]) {
				PS_swap(&bub[j], &bub[j + 1]);
				flag = 1;
			}
			count++;
			if (flag == 0) {
				printf("\n %d \n", count);
				break;
			}
		}
	}
}

void PS_swap(int* first, int* second) {
	int temp;
	temp = *first;
	*first = *second;
	*second = temp;
}
