/*
 * bitwiseFindTwoOddOccurrences.c
 *
 *  Created on: 06-Aug-2018
 *      Author: Parth shah
 */

#include<stdio.h>

void oddOccurrence(int arr[], int size) {

	int find_element_to_compare;
	int add_xor = arr[0];
	int i = 0, x = 0, y = 0;
	for (i = 1; i < size; i++) {
		add_xor = add_xor ^ arr[i];
	}
	find_element_to_compare = add_xor & ~(add_xor - 1);

	printf(" find_element_to_compare = %d ", find_element_to_compare);

	for (i = 0; i < size; i++) {
		if (arr[i] & find_element_to_compare) {
			x = x ^ arr[i];
		}else{
			y = y ^ arr[i];
		}
	}
	printf("\n x=%d,  y=%d \n",x,y);

}

int main() {
	int arr[] = { 2, 3, 2, 4, 5, 4, 5, 7, 8, 3 };
	int size;
	size = sizeof(arr) / sizeof(arr[0]);
	oddOccurrence(arr, size);
	return 0;
}

