/*
 * quickSort.c
 *
 *  Created on: 17-Jul-2018
 *      Author: Parth shah
 */



#include <stdio.h>

/* divide and conquer strategy and more faster the practical scenario average case(O(n log n)) worst case **
 *  (O(n2))	*/


/********** 7, 2, 1, 6, 8, 5, 3, 4 **************
 ********** 4 is pivot  *************************
 ********** 2 7 1 6 8 5 3 4 *********************
 ********** 2 1 7 6 8 5 3 4 *********************
 ********** 2 1 7 6 9 5 3 4 *********************
 ********** 2 1 7 6 9 5 3 4 *********************
 ********** 2 1 7 6 9 5 3 4 *********************
 ********** 2 1 3 6 9 5 7 4 *********************
 **********  re-arranging the pivot value *******
 ********** 2 1 3 4 9 5 7 6 ********************/

void PS_swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int PS_partition(int* quick, int start, int end) {
	int pivot = quick[end], i = 0;   //select the pivot i.e last element

	for (i = start; i < end; i++) {
		if (quick[i] <= pivot) {   // if value is less the pivot putting left side.
			PS_swap(&quick[start], &quick[i]);
			start++;
		}
	}
	PS_swap(&quick[start], &quick[end]); // interchanging pivot value to there specific segment.
	return start;
}

void PS_quickSort(int* quick, int start, int end) {

	if (start > end) { //return if segment is less / invalid value
		return;
	}
	int pivotIndex;
	//picking pivot and sorting like small then pivot left and greater right side and return the pivot
	pivotIndex = PS_partition(quick, start, end);

	//divide and arrange with the help of partition function
	PS_quickSort(quick, start, pivotIndex - 1);

	PS_quickSort(quick, pivotIndex + 1, end);

}

int main() {
	int sort[] = { 7, 2, 1, 6, 8, 5, 3, 4 }, size, i;
	size = sizeof(sort) / sizeof(sort[0]);

	printf("\n");
	printf("\n before sorting = ");
	for (i = 0; i < size; i++)
		printf(" %d ", sort[i]);

	PS_quickSort(sort, 0, size - 1);

	printf("\n after sorting  = ");

	for (i = 0; i < size; i++)
		printf(" %d ", sort[i]);
	printf("\n");
	return 0;
}

