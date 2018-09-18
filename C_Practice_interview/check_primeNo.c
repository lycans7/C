/*
 * check_primeNo.c
 *
 *  Created on: 12-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int val, temp, i;
	printf("\n Enter the number to check prime Number \n\t");
	scanf("%d", &val);
	if (val == 1 | val == 2 | val == 3 | val == 0) {
		printf("\n Number is prime = %d \n", val);
		exit(0);
	}
	temp = 0;
	i = 2;
	while (i <= val / 2) {
		temp = val%i;
		if(temp == 0){
			printf("\n Number is not prime = %d \n",val);
			exit(0);
		}
		i++;
	}
	printf("\n Number is prime = %d \n",val);

	return 0;
}

