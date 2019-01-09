/*
 * reverse_A_Number.c
 *
 *  Created on: 07-Jan-2019
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {
	int a = 152;
	int rem = 0, ans = 0;
	printf("\n Before reverse a Number %d \n",a);
	while (a > 0) {
		rem = a % 10;
		ans = ans * 10 + rem;
		a = a / 10;
	}
	printf("\n After reverse a Number %d \n",ans);
	return 0;
}

