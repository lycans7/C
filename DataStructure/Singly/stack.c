/*
 * stack.c
 *
 *  Created on: 12-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int count = -1;


int PS_underFlow() {
	if (count < 0) {
		return 1;
	}
	return 0;
}
int PS_overFlow() {
	if (count >= SIZE - 1) {
		return 1;
	}
	return 0;
}

void PS_top(int* str) {
	if (PS_underFlow()) {
		printf("\n ERROR!!:: Stack is empty \n");
		return;
	}
	printf("\n top = %d pos = %d \n", str[count],count);
}

void PS_pop(int *str) {
	if (PS_underFlow()) {
		printf("\n ERROR!!:: Stack is empty \n");
		return;
	}
	str[count--] = 0;
	PS_top(str);
}
void PS_push(int* str,int data) {
	if (PS_overFlow()) {
		printf("\n ERROR!!:: Stack is Full \n");
		return;
	}
	str[++count] = data;
	PS_top(str);
}



int main() {
	int stack[10] = { 0 };
	PS_top(stack);
	PS_pop(stack);
	PS_push(stack,2);
	PS_push(stack,3);
	PS_push(stack,4);
	PS_push(stack,5);
	PS_push(stack,6);
	PS_push(stack,7);
	PS_pop(stack);
	PS_push(stack,8);
	PS_push(stack,10);
	PS_push(stack,11);
	PS_push(stack,12);
	PS_push(stack,13);
	PS_push(stack,14);
	PS_push(stack,15);
	PS_push(stack,16);
	PS_pop(stack);
	PS_top(stack);
	PS_push(stack,17);
	PS_top(stack);
	PS_pop(stack);
}

