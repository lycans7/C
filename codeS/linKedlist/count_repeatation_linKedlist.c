/****************************************************
*													*
*	         count repetition linKed list           *
*              KartiK : kartikdb@cdac.in            *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void add_node();
int count_repeatation();
void display();
void display_all();



struct node
{
	int data;
	struct node *link;
}*start,*ptr,*q,*temp;

int n,count=0,num;
int res,d;
void main()
{
	char ch;
	int c;

	printf("Enter how many nodes do you want :: ");
	scanf("%d",&n);
	do
	{
	printf("1. Add Node\n");
	printf("2. Count Repeatation of the Element n");
	printf("3. Display\n");
	printf("4. Display All the Nodes\n");
	printf("5. Exit\n");
	
	printf("Enter the Choice :: ");
	scanf("\n%c",&ch);

	switch(ch)
	{
		case '1':
			add_node();
			break;
		case '2':
			c=count_repeatation();
			printf("The Number :: %d is repeated :: %d times\n",num,c);
			break;
		case '3':
			display();
			break;
		case '4':
			display_all();
			break;
		case '5':
			exit(0);
	}
	}while(1);

}
void add_node()
{
	int p;

	ptr=malloc(sizeof(struct node));
         	
	printf("Enter New Data :: ");
	scanf("%d",&p);
       	ptr->data=p;
	ptr->link=NULL;
	if(start==NULL)
		start=ptr;
	else
	{	
	  q=start;
	  while(q->link!=NULL)
		  q=q->link;
		  q->link=ptr;
	}
	count++;
	
	if(count==n)
		return;
	else
		add_node();	
}
int count_repeatation()
{       
	int k=0;

	printf("Enter the Number You want to Find Repeatation From List :: ");
	scanf("%d",&num);

	q=start;
	while(q!=NULL)
	{
		if(q->data==num)
			k++;
		q=q->link;
		if(k==0)
			printf("Given data is not there any number of time\n");
		
	}
	return k;
}
void display()
{
	int d,f=0;
	printf("Enter the element you want to Search :: ");
	scanf("%d",&d);

	q=start;
	while(q!=NULL)
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
{
	printf("Your all Entered Entries are :: \n");
	q=start;
	while(q!=NULL)
	{
		printf("Your element are %d\n",q->data);
		q=q->link;
	}
	return;
}

