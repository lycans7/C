/*
 * functionPointer.c
 *
 *  Created on: 26-Dec-2018
 *      Author: Parth shah
 */

#include <stdio.h>

extern int (*fun_ptr)(int a, int b);
extern int ADD(int a, int b);

void test(int a, int b) {

	fun_ptr = &ADD;
	int val = fun_ptr(a, b);
	printf(" %d ",val);
}

int main() {
	test(10,20);
	return 0;
}

