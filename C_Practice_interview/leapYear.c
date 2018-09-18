/*
 * leapYear.c
 *
 *  Created on: 12-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main() {
	int val, i;
	printf("\n Enter the number between you want to check Leap Year \n\t");
	scanf("%d%d", &i, &val);
	printf("\n Leap Year from %d to %d \n", i, val);
	for (i; i <= val; i++) {
		if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0)) {
			printf("LY = [%d]\t", i);
		}
	}
	printf("\n");
}

