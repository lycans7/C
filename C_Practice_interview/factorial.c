/*
 * factorial.c
 *
 *  Created on: 10-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main() {
	int fact_val, buf = 1, temp = 0;
	printf("\n Enter the value for factorial \n\t");
	scanf("%d", &fact_val);
	temp = fact_val;
	while (fact_val > 0) {
		printf("\n %d \n",fact_val);
		buf *= fact_val;
		fact_val--;
	}
	printf("\n Factorial = %d, = %d \n", temp, buf);
}

