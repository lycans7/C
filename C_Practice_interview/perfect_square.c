/*
 * perfect_square.c
 *
 *  Created on: 11-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {

	int val, i = 1, temp = 0;
	printf("\n Enter the number \n");
	scanf("%d", &val);
	while (temp < val) {
		i++;
		temp = i * i;
	}

	if (temp == val)
		printf("\n perfect square of = %d \n", i);
	else
		printf("\n Not a perfect square = %d \n", val);
	return 0;
}

