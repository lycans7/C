/*
 * selectionSort.c
 *
 *  Created on: 16-Jul-2018
 *      Author: Parth shah
 */

/****************** Inter changing the index lower with current , like 2 pos to 8 pos.  7 - 0**
 *******************answer get pos 2 = 0 , pos 8 get 7 value**********************************/

#include <stdio.h>

void PS_selectionSort(int *sel, int size);

int main() {
	int sort[] = {5,45,2,7,4,3,4}, len;
	printf("\n %d %d %d %d %d %d %d \n", sort[0], sort[1], sort[2], sort[3],
			sort[4], sort[5],sort[6]);
	len = sizeof(sort) / sizeof(sort[0]);
	printf("\n %d \n", len);

	PS_selectionSort(sort, len);

	printf("\n %d %d %d %d %d %d %d \n", sort[0], sort[1], sort[2], sort[3],
			sort[4], sort[5],sort[6]);

	return 0;
}

void PS_selectionSort(int *sel, int size) {

	int i, i_min, j,temp;
	for (i = 0; i < size - 1; i++) {
		i_min = i;							//initialized the index.
		for (j = i + 1; j < size; j++) {
			if (sel[j] < sel[i_min]) {
				i_min = j; 					//update the index of minimum value.
			}
		}
		temp = sel[i]; 						//inter-change the value of minimum index to respective.
		sel[i] = sel[i_min];
		sel[i_min] = temp;
	}

}
