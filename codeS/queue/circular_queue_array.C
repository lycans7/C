/*****************************************************************************************
*                                 circular queue using array                             *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/

#include<conio.h>
#include<stdio.h>
#define MAX 5
int front=0,rear=0,queue[MAX],count=0;

void enqueue(int item)
{								// item is new number
	if(count<MAX)
	{						//check queue full condition
		queue[rear++]=item;
		count++;
		if(rear==MAX)		//making entry circular
			rear=0;
	}
	else
		printf("queue reached max value\n");
}//end of enqueue

void dequeue(void)
{
	if(count!=0)
	{
		printf("element Dequeued is :%d\n",queue[front++]);
		count--;
		if(front==MAX)		//making exit circular
			front =0;
	}
	else
		printf("queue empty!!\n");
}//end of dequeue
void display(void)
{
	int n=count,i=front;
	while(n!=0)
	{			//printing all elements using count
		if(i==MAX)
			i=0;
		printf("%d\t f=%d\t r=%d\n",queue[i++],i,rear);
		n--;
	}
	printf("\n");
}
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
