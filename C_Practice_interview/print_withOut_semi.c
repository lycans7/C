/*
 * print_withOut_semi.c
 *
 *  Created on: 12-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {

	if (!printf("\n Hello world \n")) {

	} else
		printf("\n How are you \n");

	if (!printf("\n I am fine \n"))
		;
	else
		printf("\n What about you \n");
	return 0;
}

