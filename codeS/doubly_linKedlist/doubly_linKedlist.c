/****************************************************
*													*
*	              doubly linKed list                *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<stdlib.h>

void add_node();
void search();
void display_all();

struct node
{
	struct node *prev;
	int data;
	struct node *next;
}*start,*q;

int count = 0,n;

void main()
{
	int ch;
	printf("Enter number of nodes :: ");
	scanf("%d",&n);
	do
	{
		printf("1. Add node\n2. Search\n3. display all\n4. Exit\n");
		printf("Enter Choice :: ");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
				add_node();
				break;
			case 2:	
				search();
				break;
			case 3:
				display_all();
				break;
			case 4:
				exit(0);
	}
	}while(1);
}
void add_node()
{
	struct node *ptr;
	ptr = (struct node *)malloc(sizeof(struct node));

	printf("Enter data of the node : ");
	scanf("%d",&ptr->data);

	ptr->prev = NULL;
	ptr->next = NULL;

	if(start == NULL)
	{
		start = ptr;	
		count++;
	}
	else
	{
		q = start;
		while(q->next != NULL)
			q = q->next;
	q->next = ptr;
	ptr->prev = q;
	ptr->next = NULL;
	count++;
	}
	if(count == n)
		return;
	else
		add_node();		
}
void display_all()
{
	q = start;
	while(q != NULL)
	{
		printf("Entered data is :: %d\n",q->data);
		q = q->next;
	}
}
void search()
{
	int p,f = 0;
	printf("Enter the data you want to search :: ");
	scanf("%d",&p);

	q = start;
	while(q != NULL)
	{
		if(q->data == p)
		{
			f=1;
			break;
		}
		else
			q = q->next;
	}
	if(f)
		printf("element found and is %d\n",p);
	else
		printf("error : element is not found\n");
}
