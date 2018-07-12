/*
 * circularLinkedlist.c
 *
 *  Created on: 12-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>
#include <stdlib.h>

struct circularLinkedList {
	int data;
	struct circularLinkedList* next;
};

struct circularLinkedList* PS_Insert(struct circularLinkedList* head, int val) {
	struct circularLinkedList* ptr = (struct circularLinkedList*) malloc(
			sizeof(struct circularLinkedList));
	ptr->data = val;
	ptr->next = NULL;
	if (head == NULL) {
		head = ptr;
		head->next = head;
	} else {
		ptr->next = head->next;
		head->next = ptr;
		head = head->next;
	}
	return head;
}

int PS_underFlow(struct circularLinkedList* head) {
	while (head == NULL) {
		return 1;
	}
	return 0;
}

void PS_displayLinkedList(struct circularLinkedList* head) {
	if (PS_underFlow(head)) {
		printf("\n ERROR!! : NO LINKED LIST \n");
		return;
	}
	printf(" \n ");
	struct circularLinkedList* ptr = head->next;
	while (ptr != head) {
		printf(" %d \t", ptr->data);
		ptr = ptr->next;
	}
	printf(" %d \t \n", ptr->data);
}

int main() {
	struct circularLinkedList* head = NULL;
	PS_displayLinkedList(head);
	head = PS_Insert(head, 2);
	PS_displayLinkedList(head);
	head =PS_Insert(head, 3);
	PS_displayLinkedList(head);
	head =PS_Insert(head, 4);
	head =PS_Insert(head, 5);
	head =PS_Insert(head, 6);
	head =PS_Insert(head, 7);
	PS_displayLinkedList(head);
	return 0;
}

