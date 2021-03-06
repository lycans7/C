/*
 * circularQueueLinkedList.c
 *
 *  Created on: 13-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct circularQueueLinkedList {
	int data;
	struct circularQueueLinkedList* next;
}*front = NULL, *rear = NULL;

void Display() {
	struct circularQueueLinkedList* temp = front,*temp1 = rear;
	printf("\n Display front \t = ");
	do {
		printf("%d,", temp->data);
		temp = temp->next;
	} while (temp != rear->next);
	printf("\n  rear = ");
	do {
			printf("%d,", temp1->data);
			temp1 = temp1->next;
		} while (temp1 != rear);

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
	printf("\n Peek ----->  Front == %d , rear == %d \n", front->data, rear->data);
}

void PS_enqueue(int val) {
	struct circularQueueLinkedList* ptr =
			(struct circularQueueLinkedList *) malloc(
					sizeof(struct circularQueueLinkedList));
	ptr->data = val;
	ptr->next = NULL;
	if (rear == NULL) {
		rear = front = ptr;
		rear->next = rear;
	} else {
		ptr->next = rear->next;
		rear->next = ptr;
		rear = rear->next;
	}
}

void PS_dequeue() {
	if (PS_underFlow()) {
		printf("\n ERROR!! :: Queue is empty \n");
		return;
	}
	struct circularQueueLinkedList* temp = front;
	printf("\n Dequeue = %d \n", temp->data);
	front = front->next;
	rear->next = front;
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
	PS_peek();
	return 0;
}

