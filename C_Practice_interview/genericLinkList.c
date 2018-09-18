/*
 * genericLinkList.c
 *
 *  Created on: 14-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

#define INT sizeof(int)
#define CHAR sizeof(char)
#define FLOAT_DATATYPE 5

struct node {
	void* data;
	struct node* link;
};

void Insert(struct node **head, void * data);
//void PF(struct node* head, unsigned int type_size);
void PF(struct node* head, void (*ptr)(void*));
void PF_int(void* data);
void PF_float(void* data);
void PF_char(void* data);
void DEL(struct node** head);

int main() {
	struct node *head = NULL;
	int int_size, Cmd_test, i, Int_arr[] = { 2, 3, 4, 5, 6 };
	float float_size, Float_arr[] = { 3.0, 4.1, 5.2, 6.3, 7.4 };
	char char_size, Char_arr[] = { 'A', 'B', 'C', 'D', 'E' };

	int_size = sizeof(Int_arr) / sizeof(Int_arr[0]);
	float_size = sizeof(Float_arr) / sizeof(Float_arr[0]);
	char_size = sizeof(Char_arr) / sizeof(Char_arr[0]);

	printf("\n Enter integer value \n\t");
	scanf("%d", &Cmd_test);
	// For integer value
	printf("\n Insert and print integer value \n");
	Insert(&head, &Cmd_test);
	for (i = int_size - 1; i >= 0; i--) {
		Insert(&head, &Int_arr[i]);
	}
//	PF(head, INT);
	PF(head, PF_int);
	DEL(&head);

	// For Float value
	printf("\n Insert and print Float value \n");
	for (i = float_size - 1; i >= 0; i--) {
		Insert(&head, &Float_arr[i]);
	}
//	PF(head, FLOAT_DATATYPE);
	PF(head, PF_float);
	DEL(&head);

	// For character value
	printf("\n Insert and print Char value \n");
	for (i = char_size - 1; i >= 0; i--) {
		Insert(&head, &Char_arr[i]);
	}
//	PF(head, CHAR);
	PF(head, PF_char);
	DEL(&head);

	return 0;
}

void Insert(struct node **head, void * data) {
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->link = NULL;
	temp->data = data;
	if (*head == NULL) {
		*head = temp;
	} else {
		temp->link = *head;
		*head = temp;
	}

}

/*
 void PF(struct node* head, unsigned int type_size) {
 void (*ptr)(void*);
 printf(" \n ");
 while (head) {
 if(type_size == INT){
 ptr = PF_int;
 (*ptr)(head->data);
 }
 else if(type_size == FLOAT_DATATYPE){
 ptr = PF_float;
 (*ptr)(head->data);
 }
 else if(type_size == CHAR){
 ptr = PF_char;
 (*ptr)(head->data);
 }
 head = head->link;
 }
 printf(" \n ");
 }
 */

void PF(struct node* head, void (*ptr)(void*)) {
	printf(" \n ");
	while (head) {
		(*ptr)(head->data);
		head = head->link;
	}
	printf(" \n ");
}

void DEL(struct node** head) {
	struct node* temp1 = *head;
	struct node* temp2 = NULL;
	temp2 = temp1;
	while (temp1 != NULL) {
		temp1 = temp1->link;
		free(temp2);
		temp2 = temp1;
	}

	*head = NULL;
}

void PF_int(void* data) {
	printf(" %d ", *(int*) data);
}
void PF_float(void* data) {
	printf(" %f ", *(float*) data);
}
void PF_char(void* data) {
	printf(" %c ", *(char*) data);
}
