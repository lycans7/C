/*
 * printfIfAndElseBothSimultaneously.c
 *
 *  Created on: 27-Nov-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main(){

	if(1){
		label1:

		printf("Hello");
		goto label2;
	}
	else
		goto label1;

		label2 : printf("\tParth");
	return 0;
}

