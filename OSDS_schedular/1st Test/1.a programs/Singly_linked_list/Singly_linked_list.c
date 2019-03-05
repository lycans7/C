/*
 * Singly_linked_list.c
 *
 *  Created on: 08-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	"link_function_declare.h"


int main()
{
	struct node* head = NULL;

	int iResult = 0,iVal = 0;

	printf("Start with head value:");
	scanf("%d",&iVal);
	head = Create_Node(iVal);

	while(1)
	{
		iResult = Push(&head);
		if(iResult == 1)
		{
			iResult = 0;
			break;
		}
	}
	while(1)
	{
		iResult = Add_At_Tail(&head);
		if(iResult == 1)
		{
			iResult = 0;
			break;
		}
	}


	printf("\nCreated list");
	Print_List(&head);

	Recursive_Reverse(&head);

	printf("\n\nReverse of the list");
	Print_List(&head);

	Destroy_List(&head);

	return 0;
}




