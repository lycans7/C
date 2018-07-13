/*
 * queue.c
 *
 *  Created on: 12-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int rear = -1, front = -1;

int PS_isEmpty() {
	if (rear < 0) {
		return 1;
	}
	return 0;
}

int PS_isFull() {
	if (rear >= SIZE - 1 || front >= SIZE - 1) {
		return 1;
	}
	return 0;
}

void PS_peek(int* frnt) {
	if (PS_isEmpty()) {
		printf("\n ERROR!!:: QUEUR is empty \n");
		return;
	}
	printf(
			"\n  Front position == %d ,position rear = %d , front = %d ,rear = %d  \n",
			front, rear ,frnt[front],frnt[rear]);
}

void PS_enQueue(int* queue, int val) {
	if (PS_isFull()) {
		printf("\n ERROR!!:: QUEUR is Full \n");
		return;
	}
	if (PS_isEmpty()) {
		front = 0;
	}
	queue[++rear] = val;
	PS_peek(queue);
}

void PS_deQueue(int* queue) {
	if (PS_isFull()) {
		printf("\n ERROR!!:: QUEUR is Full \n");
		return;
	}
	if (PS_isEmpty()) {
		printf("\n ERROR!!:: QUEUR is Empty \n");
		return;
	}
	if (front >= rear) {
		printf("\n ERROR!!:: QUEUR is Full \n");
		return;
	}
	queue[front++] = 0;
	PS_peek(queue);
}

int main() {
	int queue[SIZE] = { 0 };
	PS_peek(queue);
	PS_peek(queue);
	PS_enQueue(queue, 2);
	PS_enQueue(queue, 3);
	PS_enQueue(queue, 4);
	PS_enQueue(queue, 5);
	PS_enQueue(queue, 6);
	PS_deQueue(queue);
	PS_deQueue(queue);
	PS_enQueue(queue, 7);
	PS_deQueue(queue);
	PS_deQueue(queue);
	PS_deQueue(queue);
	PS_deQueue(queue);
	PS_enQueue(queue, 8);
	PS_enQueue(queue, 9);
	PS_enQueue(queue, 10);
	PS_enQueue(queue, 11);
	PS_enQueue(queue, 12);
	PS_peek(queue);
	return 0;
}

