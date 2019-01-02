/*
 * withoutMainFunction.c
 *
 *  Created on: 27-Nov-2018
 *      Author: Parth shah
 */

/*
#include<stdio.h>
#include<stdlib.h>
// entry point function
int abc();

void _start() {

	// calling entry point
	abc();
	exit(0);
}

int abc() {
	puts("Hello start");
	return 0;
}

//compile with  (gcc filename.c -nostartfiles )
*/

/* Second method */

#include <stdio.h>

#define nomain main

int nomain(){
	printf("Hello world");
	return 0;
}
