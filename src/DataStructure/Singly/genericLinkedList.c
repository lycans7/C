/*
 * genericLinkedList.c
 *
 *  Created on: 18-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
	void *data;
	struct node *next;
}*head = NULL;

void display() {
	struct node *ptr = head;
	while (ptr != NULL) {
		printf("%f \n", *((float*) ptr->data));
		ptr = ptr->next;
	}
}

void insert(int val) {
	struct node *ptr = (struct node *) malloc(sizeof(struct node));
	ptr->data = malloc(sizeof(int));
	*((int*) ptr->data) = val;
	printf("%d \n", *((int*) ptr->data));
	ptr->next = NULL;
	if (head == NULL) {
		head = ptr;
	} else {
		ptr->next = head;
		head = ptr;
	}
}

void insert_Float(float val) {
	struct node *ptr = (struct node *) malloc(sizeof(struct node));
	ptr->data = malloc(sizeof(float));
	*((float*) ptr->data) = val;
	printf("%f \n", *((float*) ptr->data));
	ptr->next = NULL;
	if (head == NULL) {
		head = ptr;
	} else {
		ptr->next = head;
		head = ptr;
	}

}
int main() {
	insert(2);
	insert(3);
	insert(4);
	insert_Float(5.6);
	insert_Float(7.8);
	insert_Float(10.00);
	insert_Float(11.2);
	display();
	return 0;
}

