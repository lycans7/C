/*
 * sizeof.c
 *
 *  Created on: 23-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {
	int cons, unsig_int, sig_int, voli, dataA, dataB;
	cons = sizeof(const);
	unsig_int = sizeof(unsigned);
	sig_int = sizeof(signed);
	voli = sizeof(volatile);
	dataA = sizeof(signed) + sizeof(unsigned);
	dataB = sizeof(const) + sizeof(volatile);
	printf(
			"\n constant = %d \n unsigned integer = %d \n signed integer = %d \n volatile = %d \n "
					"dataA + dataB = %d \n", cons, unsig_int, sig_int, voli,
			dataA + + +dataB);//printf left to right

	return 0;
}

