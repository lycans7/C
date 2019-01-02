/*
 * selectionSort.c
 *
 *  Created on: 24-Dec-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void Ps_selectionSort(int p[], int len);

void Ps_sort(int *fst, int* lst);

int main() {
	int ARR_SIZE;
	printf("Enter the Array size \n");

	scanf("%d", &ARR_SIZE);

	printf("Enter the Value, Size is not more then %d \n", ARR_SIZE);

	int arr[ARR_SIZE], i;

	for (i = 0; i < ARR_SIZE; i++) {
		if (i < ARR_SIZE)
			scanf("%d", &arr[i]);
	}

	Ps_selectionSort(arr, ARR_SIZE);

	for (i = 0; i < ARR_SIZE; i++) {
		printf(" %d ", arr[i]);
	}

	printf("\n");
	return 0;
}

void Ps_selectionSort(int p[], int len) {
	int i, index, j;
	for (i = 0; i < len; i++) {
		index = i;
		for (j = i + 1; j < len; j++) {
			if (p[j] < p[index])
				index = j;
		}
		Ps_sort(&p[index], &p[i]);
	}
}

void Ps_sort(int *fst, int* lst) {

	int temp = *lst;
	*lst = *fst;
	*fst = temp;

}
