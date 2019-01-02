#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *linK;
}*start,*ptr,*q;

void create(void)
{
	ptr = malloc(sizeof(struct node));
	printf("Enter the data to the node :: ");
	scanf("%d",&ptr -> data);
	ptr -> linK = NULL;

	if(start == NULL)
		start = ptr;
	else
	{
		q = start;
		while(q -> linK != NULL)
			q = q -> linK;
		q -> linK = ptr;
	}
}
void display(void)
{
	q = start;
	while(q != NULL)
	{
		printf("%d\t",q -> data);
		q = q -> linK;
	}
	printf("\n");
}
void reverse(struct node *tmp)
{
	if(tmp == NULL || tmp -> linK == NULL)
	{
		start = tmp;
		return;
	}
	reverse(tmp -> linK);					// traverse till the second last node and then maKe (last node linK = prev node) and
	tmp -> linK -> linK = tmp;				// continue till the start of linKed list and assign linK of first node = NULL
	tmp -> linK = NULL;
}
void main()
{
	int ch;
	while(2)
	{
		printf("1. create\n2.Reverse the nodes\n3. Display\nEnter the choice :: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				create();	break;
			case 2:
				reverse(start);	break;
			case 3:
				display();	break;
			default:
				printf("Invalid choice .. \n");
				exit(0);
		}
	}
}		
