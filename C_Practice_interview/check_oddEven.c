/*
 * check_oddEven.c
 *
 *  Created on: 12-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

void main() {
	int val;
	printf("\n Enter the number to check Odd and Even \n\t");
	scanf("%d", &val);
	if(val == 0){
		printf("\n Enter number is Even = %d \n",val);
		exit(0);
	}
	if(val%2 == 0)
		printf("\n Enter number is Even = %d \n",val);
	else
		printf("\n Enter number is Odd = %d \n",val);
}

