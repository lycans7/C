/****************************************************
*													*
*	           queue using linKed list              *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
typedef struct queue
{
	int data;
	struct queue *nxt;
} queue;
queue *front,*rear;

void enqueue(int item)
{
	queue *new;
	new=malloc(sizeof(queue));
	new->data=item;
	new->nxt=NULL;
	if(front==NULL)
	{
		front=new;
		rear=front;
	}
	else
	{
		rear->nxt=new;
		rear=new;
	}
}//end of enqueue

void dequeue(void)
{
	queue *temp=front;
	if(front!=NULL)
	{
		printf("element Dequeued is :%d\n",front->data);
		front=front->nxt;
		free(temp);
	}
	else
		printf("queue empty!!\n");

}//end of dequeue

void display(void)
{
	queue *temp=front;
	while(temp!=NULL)
	{
		printf("%d\t",temp->data);
		temp=temp->nxt;
	}
	printf("\n");
}//end of display

void main()
{
	int c=1,item;
	while(c)
	{
		printf("1:enqueue\n2:dequeue\n3:display\n0:exit\nchoose the option:");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				printf("enter the element:");
				scanf("%d",&item);
				enqueue(item);
				break;
			case 2:
				dequeue();
				break;
			case 3:
				display();
				break;
			case 0:
				break;
			default:
				printf("invalid option\n");
		}//end of switch
	}//end of while
}//end of main
