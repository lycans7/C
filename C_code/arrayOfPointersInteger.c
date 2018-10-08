/*
 * arrayOfPointersInteger.c
 *
 *  Created on: 09-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {
	int arr[] = { 8, 9, 6, 4 };
	int *a[4];
	int size, i;
	size = sizeof(arr) / sizeof(arr[0]);

	for (i = 0; i < size; i++) {
		printf("\n %d \n", arr[i]);
		a[i] = &arr[i];
		printf("\n %p %d \n", a[i], *a[i]);
	}

	return 0;
}

