/****************************************************
*													*
*	               linKed list                      *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void add_node();
void search();
void display();
void display_all();
void reverse();
void sort();
void delete();
void reverse_recursive(struct node *);

struct node
{
	int data;
	struct node *link;
}*i,*j,*start,*ptr,*q,*temp,*p1,*p2,*p3;

int n,count=0;

void main()
{
	char ch;

	printf("Enter how many nodes do you want :: ");
	scanf("%d",&n);
	do
	{
	printf("1. Add Node\n");
	printf("2. Search\n");
	printf("3. Display\n");
	printf("4. Display All the Nodes\n");
	printf("5. Reverse the Nodes\n");
	printf("6. Sort\n");
	printf("7. Delete\n");
	printf("8. Exit\n");
	printf("9. reverse linKedlist recursively\n");

	printf("Enter the Choice :: ");
	scanf("\n%c",&ch);

	switch(ch)
	{
		case '1':
			add_node();
			break;
		case '2':
			search();
			break;
		case '3':
			display();
			break;
		case '4':
			display_all();
			break;
		case '5':
			reverse();
			break;
		case '6':
			sort();
			break;
		case '7':
			delete();
			break;
		case '8':
			exit(0);
			break;
		case '9':
			reverse_recursive(start);
			start -> link = NULL;
			break;
	}
	}while(1);

}
void add_node()
{
	int p;

	ptr=(struct node *)malloc(sizeof(struct node));

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
	printf("count is %d\n",count);
	if(count==n)
		return;
	else
		add_node();
}
void search()
{
	int d;

	printf("Enter the Data you want to Search :: ");
	scanf("%d",&d);

	q=start;
	while(q!=NULL)
	{
		if(q->data==d)
			printf("Element is Found. It is %d \n",q->data);
		else
			printf("Element is not found\n");
		q=q->link;
	}
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
void reverse()
{
	p1=start;
	p2=p1->link;
	p3=p2->link;
	p1->link=NULL;
	p2->link=p1;
	while(p3!=NULL)
	{
		p1=p2;
		p2=p3;
		p3=p3->link;
		p2->link=p1;
		start=p2;
	}
	display_all();
}
void reverse_recursive(struct node *tmp)
{
	if(tmp)
	{
		reverse_recursive(tmp -> link);
		tmp -> link -> link = tmp;
	}
	start = tmp;
	display_all();
}
void sort()
{
	q=start;
	for(i=q;i!=NULL;i=i->link)
	{
		for(j=i->link;j!=NULL;j=j->link)
		{
			if((i->data)> (j->data))
			{
				temp=j->data;
				j->data=i->data;
				i->data=temp;
			}
		}
	}
	display_all();
}
void delete()
{
	int pos;
	printf("Enter the position you want to delete : ");
	scanf("%d",&pos);

	q=start;
	if(pos==1)
	{
		temp=start;
		start=start->link;
		free(temp);
		return;
	}					//Deletion in Begining

	else
	{
		while((pos-2)!=0)
		{
			q=q->link;
			pos--;
		}
		temp=q->link;
		q->link=temp->link;
		free(temp);
		return;
	}			//Deletion in between
	while(q->link!=NULL)
	{
		temp=q->link;
		free(temp);
	}					//Deletion in the End
	display_all();
}
