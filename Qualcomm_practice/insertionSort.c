/*
 * insertionSort.c
 *
 *  Created on: 24-Dec-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void PS_insertion(int a[], int len);

int main() {
	int SIZE, i;

	printf("Enter the size of array \n");

	scanf("%d", &SIZE);

	printf("Enter the Value of array, input not more than %d \n", SIZE);

	int arr[SIZE];

	for (i = 0; i < SIZE; i++)
		scanf("%d", &arr[i]);
	printf("Before Sort \n");
	for (i = 0; i < SIZE; i++)
		printf("a[%d] = %d ", i, arr[i]);

	PS_insertion(arr, SIZE);

	printf("After Sort \n");

	for (i = 0; i < SIZE; i++)
		printf("a[%d] = %d ", i, arr[i]);
	printf("\n");
	return 0;
}

void PS_insertion(int a[], int len) {
	int i, j, val;

	for (i = 0; i < len; i++) {
		val = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > val) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = val;
	}

}
