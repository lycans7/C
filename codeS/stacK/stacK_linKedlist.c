/*****************************************************************************************
*                                   stacK using linKed list                              *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

void push();
void pop();
void display_all();
						//stack using linked list
struct node
{
	int data;
	struct node *link;
}*start,*ptr,*top_most,*q;

int top=0;

void main()
{
	char ch;
	do
	{
		printf("1. Push into Stack\n");
		printf("2. Pop From the Stack\n");
		printf("3. Display all elements of the Stack\n");
		printf("4. Exit\n");

		printf("Enter the Choice ::: ");
		scanf("\n%c",&ch);

		switch(ch)
		{
			case '1':
				push();
				break;
			case '2':
				pop();
				break;
			case '3':
				display_all();
				break;
			case '4':
				exit(0);
		}
	}while(1);	
}
void push()
{
	ptr=malloc(sizeof(struct node));

	printf("Enter the data to be pushed :: ");
	scanf("%d",&ptr->data);

	ptr->link=NULL;

	if(start==NULL)
		start=ptr;
	else
	{
		ptr->link=start;
		start=ptr;
	}
	top++;printf("The value of top is %d\n",top); // int top=0
}
void pop()
{
	if(top)
	{
		printf("Popped element is :: %d\n",start->data);
		q=start;
		start=start->link;
		free(q);
		top--;
	}
	else
	{
		printf("Stack is empty !!!\n");
		return;
	}
}

void display_all()
{
	q=start;
	while(q!=NULL)
	{
		printf("Your Entered data is %d :: \n",q->data);
		q=q->link;
	}
}

