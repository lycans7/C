/*
 * mergeSort.c
 *
 *  Created on: 17-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void PS_mergeSort(int arr[], int startpos, int midpos, int lastpos) {
	int i, j, k, len_arr1, len_arr2;

	len_arr1 = midpos - startpos + 1; 	//size of dummy array
	len_arr2 = lastpos - midpos;		//size of dummy array

	int arr1[len_arr1], arr2[len_arr2];

	for (i = 0; i < len_arr1; i++) {	//filling dummy array with actual array data
		arr1[i] = arr[startpos + i];
	}
	for (j = 0; j < len_arr2; j++) {
		arr2[j] = arr[midpos + 1 + j];
	}
	i = j = 0;
	k = startpos;	  //starting position of actual array

	/**************filling actual array with sorted value of dummy array ******/
	while (i < len_arr1 && j < len_arr2) {
		if (arr1[i] <= arr2[j]) {
			arr[k] = arr1[i];
			i++;
		} else {
			arr[k] = arr2[j];
			j++;
		}
		k++;
	}

	/******** any of the dummy array left then if directly to actual array*****
	 ******** because any one of the dummy array will left********************/
	while (i < len_arr1) {
		arr[k] = arr1[i];
		i++;
		k++;
	}

	while (j < len_arr2) {
		arr[k] = arr2[j];
		j++;
		k++;
	}
}

/*********************  10, 4, 2, 6, 8, 1, 5, 11 *********************
 *	 	 	 		r[10,4,2,6] ********* l[8,1,5,11]
 * 		 r[10,4]----l[2,6]******************* r[8,1]----l[5,11]
 * 	r[10]---l[4]*****r[2]---l[6]**************r[8]---l[1]*****r[5]----l[11]
 *
 *
 * 	r[4]---l[10]*****r[2]---l[6]**************r[1]---l[8]*****r[5]----l[11]
 * 	  		 r[4,10]----l[2,6]******************* r[1,8]----l[5,11]
 * 	  		            r[2,4,6,10] ********* l[1,5,8,11]
 * ***********************  1, 2, 4, 5, 6, 8, 10, 11 ********************/

void PS_merge(int mer[], int start, int end) {

	if (start < end) {

		int mid = start + (end - start) / 2; //finding the middle element

		PS_merge(mer, start, mid);	//recursive call to left half
		PS_merge(mer, mid + 1, end); //recursive call to right

		PS_mergeSort(mer, start, mid, end); //after divide and conquer again save in sorted order.
	}
}

int main() {
	int sorting[] = { 10, 4, 2, 6, 8, 1, 5, 11 }, i, size;
	size = sizeof(sorting) / sizeof(sorting[0]);
	for (i = 0; i < size; i++)
		printf(" %d ", sorting[i]);

	PS_merge(sorting, 0, size - 1); //starting point of array and last .

	printf("\n Sorted =  \n");

	for (i = 0; i < size; i++)
		printf(" %d ", sorting[i]);
	printf(" \n ");
	return 0;
}

