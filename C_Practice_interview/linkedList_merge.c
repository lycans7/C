/*
 * linkedList_merge.c
 *
 *  Created on: 18-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* link;
};

void PS_Insert(struct node** head, int data);
void PS_PF(struct node* head);
void PS_mergeSort(struct node** head);
void PS_divideList(struct node* head, struct node** first, struct node** last);
struct node* PS_meargedSort(struct node* first, struct node* last);

int main() {
	struct node* head = NULL;
	PS_Insert(&head, 1);
	PS_Insert(&head, 10);
	PS_Insert(&head, 2);
	PS_Insert(&head, 5);
	PS_Insert(&head, 8);
	PS_Insert(&head, 12);
	PS_PF(head);
	PS_mergeSort(&head);
	PS_PF(head);
}

void PS_Insert(struct node** head, int data) {
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->data = data;
	temp->link = *head;
	*head = temp;
}
void PS_PF(struct node* head) {
	printf("\n");
	while (head != NULL) {
		printf(" %d ", head->data);
		head = head->link;
	}
	printf("\n");
}
void PS_mergeSort(struct node** head) {
	struct node* temp = *head;
	struct node* a;
	struct node* b;
	if (temp == NULL || temp->link == NULL) {
		return;
	}
	PS_divideList(temp, &a, &b);
	PS_mergeSort(&a);
	PS_mergeSort(&b);

	*head = PS_meargedSort(a, b);
}
void PS_divideList(struct node* head, struct node** first, struct node** last) {
	struct node* slow, *fast;
	slow = head;
	fast = head->link;
	while (fast != NULL) {
		fast = fast->link;
		if (fast != NULL) {
			slow = slow->link;
			fast = fast->link;
		}
	}
	*first = head;
	*last = slow->link;
	slow->link = NULL;
}

struct node* PS_meargedSort(struct node* first, struct node* last) {
	struct node* result = NULL;
	if (first == NULL)
		return last;
	else if (last == NULL)
		return first;

	if (first->data <= last->data) {
		result = first;
		result->link = PS_meargedSort(first->link, last);
	} else {
		result = last;
		result->link = PS_meargedSort(last->link, first);
	}
	return result;
}
