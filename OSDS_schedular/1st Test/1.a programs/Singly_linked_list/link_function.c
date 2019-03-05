/*
 * link_function.c
 *
 *  Created on: 08-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	"link_function_declare.h"



/*
 * Function name	:	Create_Node
 *
 * Description		:	use this function to create a head node with user given value.
 *
 * Parameters		:	int iVal -> value given by the user for the head.
 *
 * Returns			:	pointer to the created head node
 *
 */
struct node* Create_Node(int iVal)
{
	struct node * ptr = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	if(ptr != NULL)
	{
		ptr->iData = iVal;
		ptr->next = NULL;
	}
	return ptr;
}


/*
 * Function name	:	Push
 *
 * Description		:	use this function to add the value at the front of the existing head node.
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	0 if user adds the value
 * 						1 if user does not want to add a value.
 *
 */
int Push(struct node **head)
{
	struct node* newnode = NULL;

	int iVal = 0,iResult = 0;
	char cCh;

	printf("Do you want to add data at head? press y/n:");
	cCh = getchar();

	if((cCh == 'y')||(cCh == 'Y'))
	{
		printf("Enter your data:");
		scanf("%d",&iVal);
		newnode = (struct node*)malloc(sizeof(struct node));
		iResult = 0;
	}
	else if((cCh == 'n')||(cCh == 'N'))
	{
		return 1;
	}

	if(newnode != NULL)
	{
		newnode->iData = iVal;
		newnode->next = *head;
		*head = newnode;
	}
	return iResult;
}


/*
 * Function name	:	Add_At_Tail
 *
 * Description		:	use this function to add the user given value at end of
 * 						linked list.
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	0 if user adds the value
 * 						1 if user does not want to add a value.
 *
 */
int Add_At_Tail(struct node **headref)
{
	struct node *current = *headref;
	struct node *newnode = NULL;

	int iVal = 0, iResult = 0;
	char cCh;

	printf("Do you want to add data at tail? press y/n:");
	cCh = getchar();

	if((cCh == 'y')||(cCh == 'Y'))
	{
		printf("Enter your data:");
		scanf("%d",&iVal);
		newnode = (struct node*)malloc(sizeof(struct node));
		iResult = 0;
	}
	else if((cCh == 'n')||(cCh == 'N'))
	{
		return 1;
	}

	if(newnode != NULL)
	{
		newnode->iData = iVal;
		newnode->next = NULL;
	}

	while(current->next != NULL)
	{
		current = current->next;
	}
	if(newnode != NULL)
	{
		current->next = newnode;
	}
	return iResult;
}


/*
 * Function name	:	Print_List
 *
 * Description		:	use this function to print all the values listed
 * 						in linked list.
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	None
 *
 */
void Print_List(struct node **head)
{
	struct node *current = *head;

	while(current != NULL)
	{
		printf("\nData is %d",current->iData);
		current = current->next;
	}
}


/*
 * Function name	:	Recursive_Reverse
 *
 * Description		:	use this function to reverse the order of the linked list
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	None
 *
 */
void Recursive_Reverse(struct node** head_ref)
{
    struct node* first;
    struct node* rest;

    if (*head_ref == NULL)
       return;

    first = *head_ref;
    rest  = first->next;

    if (rest == NULL)
       return;

    Recursive_Reverse(&rest);
    first->next->next  = first;

    first->next  = NULL;

    *head_ref = rest;
}


/*
 * Function name	:	Destroy_List
 *
 * Description		:	use this function to delete the linked list.
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	None
 *
 */
void Destroy_List(struct node **headref)
{
	struct node *first = *headref;
	struct node *rest = NULL;

	rest = first->next;

	if(rest == NULL)
	{
		free(rest);
		return;
	}
	Destroy_List(&rest);
}


/*
 * Function name	:	Length
 *
 * Description		:	use this function to find the length of the list
 *
 * Parameters		:	struct node ** -> pointer to the head node.
 *
 * Returns			:	the length of the list
 *
 */
int Length(struct node* head)
{
	int count = 0;
	struct node* current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}


//void push(struct node **head,int val)
//{
//	struct node* newnode = NULL;
//
//	newnode = (struct node*)malloc(sizeof(struct node));
//	if(newnode != NULL)
//	{
//		newnode->data = val;
//		newnode->next = *head;
//		*head = newnode;
//	}
//}
