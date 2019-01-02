/****************************************************
*													*
*	   division of linKed list into two parts       *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void add_node_circular();	
void division();                                     
void search();
void display_all();

struct node
{
	int data;
	struct node *link;
}*last,*ptr,*q,*p1,*p2;

int d,n,count=0;

void main()
{
	char ch;   

	printf("Enter nodes you want in Circular Linked List :: ");
	scanf("%d",&n);
	do
	{
	printf("1. Add Node\n");
	printf("2. Print parts of Circular list\n");
	printf("3. Search\n");
	printf("4. Display All the Nodes\n");
	printf("5. Exit\n");

	printf("Enter the Choice :: ");
	scanf("\n%c",&ch);

	switch(ch)
	{
		case '1':
			add_node_circular();
			break;
		case '2':
			division();
			break;
		case '3':
			search();
			break;
		case '4':
			display_all();
			break;
		case '5':
			exit(0);
	}
	}while(1);
	getch();
}
void add_node_circular()
{
	int p;

	ptr=malloc(sizeof(struct node));

	printf("Enter New Data :: ");
	scanf("%d",&p);

	ptr->data=p;

	if(last==NULL)
	{
		last=ptr;
		last->link=last;
	}
	else
	{	
		ptr->link=last->link;
		last->link=ptr;          // we are adding nodes at beginning all the time
		last=ptr;                // here last is acting as start. but last is actually last node only
	}
	count++;
	printf("%d\n",count);
	if(count!=n)
		add_node_circular();	
	else
		return;
}
void division()
{
	int k=count/2;                          // k=2
	int l=k;
	int c=k;

	q=last;

	while(k!=0)
	{
		q=q->link;
		k--;
	}
	p1=q;
	p2=q->link;
	p1->link=last->link;
	last->link=p2;
	p2=last;


	printf("Element of first part:: \n");

	while(l!=0)
	{
		printf("element are :: %d\n",p1->link->data);
		p1=p1->link;
		l--;
	}

	printf("Second Part of List is\n");

	while(c!=count)
	{
		p2=p2->link;
		printf("Elements are :: %d\n",p2->data);
		c++;
	}

}
void search()
{
	int f=0;
	printf("Enter the element you want to Search :: ");
	scanf("%d",&d);

	q=last->link;
	while(q!=last)
	{
		if(q->data==d)
		{
			f=1;
			break;
		}
		else
			f=0;
		q=q->link;
	}
	if(f)
			printf("Data is Found and it is %d \n",q->data);
	else
			printf("Entered Entry isnt there \n");


}
void display_all()
{	int c=count;
	printf("Your all Entered Entries are :: \n");
	q=last->link;
	while(c!=0)
	{
		printf("Your element are %d\n",q->data);
		q=q->link;
		c--;
	}
	return;
}


