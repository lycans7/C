/*
 * queueLinkedList.c
 *
 *  Created on: 13-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct queueLinkedList {
	int data;
	struct queueLinkedList* next;
}*front = NULL, *rear = NULL;

void Display() {
	struct queueLinkedList* temp = front;
	printf("Display \t = ");
	while (temp != NULL) {
		printf("%d,", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int PS_underFlow() {
	if (rear == NULL) {
		return 1;
	}
	return 0;
}

void PS_peek() {
	if (PS_underFlow()) {
		printf("\n ERROR!! :: Queue is empty \n");
		return;
	}
	printf("\n Front == %d , rear == %d \n", front->data, rear->data);
}

void PS_enqueue(int val) {
	struct queueLinkedList* ptr = (struct queueLinkedList *) malloc(
			sizeof(struct queueLinkedList));
	ptr->data = val;
	ptr->next = NULL;
	if (rear == NULL) {
		rear = front = ptr;
	} else {
		rear->next = ptr;
		rear = rear->next;
	}
}

void PS_dequeue() {
	if (PS_underFlow()) {
		printf("\n ERROR!! :: Queue is empty \n");
		return;
	}
	struct queueLinkedList* temp = front;
	printf("\n Dequeue = %d \n", temp->data);
	front = front->next;
	free(temp);
}

int main() {
	PS_peek();
	PS_dequeue();
	PS_enqueue(3);
	PS_enqueue(4);
	PS_enqueue(5);
	PS_enqueue(6);
	PS_enqueue(7);
	PS_enqueue(8);
	PS_enqueue(9);
	Display();
	PS_peek();
	PS_dequeue();
	PS_peek();
	PS_dequeue();
	PS_enqueue(10);
	PS_enqueue(11);
	PS_enqueue(12);
	PS_peek();
	Display();
	return 0;
}
