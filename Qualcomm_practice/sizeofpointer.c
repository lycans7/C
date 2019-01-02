/*
 * sizeofpointer.c
 *
 *  Created on: 27-Nov-2018
 *      Author: Parth shah
 */

#include <stdio.h>

struct node {
	int data;
	struct node* link;
};

int main() {
	int* ptr;
	char* ptr1;
	float* ptr2;
	struct node* ptr3;

	printf("int = %d int* = %d int** = %d char  = %d float = %d struct = %d",sizeof(int),sizeof(int *),sizeof(ptr),sizeof(ptr1),sizeof(ptr2),sizeof(ptr3));

	return 0;
}

