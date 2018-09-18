/*
 * swap_2nos_Nt3var.c
 *
 *  Created on: 11-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main() {
	int val, val1;
	printf("\n Enter two numbers to swap XOR \n \t");
	scanf("%d%d", &val, &val1);
	printf("\n Enter number val = %d , val1 = %d \n", val, val1);
	val = val ^ val1;
	val1 = val ^ val1;
	val = val ^ val1;
	printf("\n After swap val = %d , val1 = %d \n", val, val1);


	printf("\n Enter two numbers to swap by add \n \t");
	scanf("%d%d", &val, &val1);
	printf("\n Enter number val = %d , val1 = %d \n", val, val1);
	val = val + val1;
	val1 = val - val1;
	val = val - val1;
	printf("\n After swap val = %d , val1 = %d \n", val, val1);
}

