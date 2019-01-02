/*
 * stackLinkedList.c
 *
 *  Created on: 13-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct stackLinkedlist {
	int data;
	struct stackLinkedlist* next;
}*top = NULL;

int PS_underFlow() {
	if (top == NULL) {
		return 1;
	}
	return 0;
}

void PS_peek() {
	if (PS_underFlow()) {
		printf("\n ERROR!! :: STACK IS EMPTY \n");
		return;
	}
	printf("\n -- top -- = %d \n", top->data);
}

void PS_push(int val) {
	struct stackLinkedlist* ptr = (struct stackLinkedlist*) malloc(
			sizeof(struct stackLinkedlist));
	ptr->data = val;
	ptr->next = NULL;
	if (top == NULL) {
		top = ptr;
	} else {
		ptr->next = top;
		top = ptr;
	}
	PS_peek();
}

void PS_pop() {
	if (PS_underFlow()) {
		printf("\n ERROR!! :: STACK IS EMPTY \n");
		return;
	}
	printf("\n pop = %d \n", top->data);

	struct stackLinkedlist* temp = top;
	top = top->next;
	free(temp);
}

int main() {
	PS_pop();
	PS_push(1);
	PS_push(2);
	PS_push(3);
	PS_push(4);
	PS_peek();
	PS_push(5);
	PS_push(6);
	PS_push(7);
	PS_pop();
	PS_peek();
	PS_push(8);
	PS_push(9);
	PS_pop();
	PS_peek();
	return 0;
}
