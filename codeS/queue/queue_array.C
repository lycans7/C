/****************************************************
*													*
*	              queue using array                 *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<conio.h>
#define MAX 20
int front=0,rear=0,queue[MAX];

void enqueue(int item)
{
	if(rear<MAX)
		queue[rear++]=item;
	else
		printf("queue reached max value\n");
}//end of enqueue

int dequeue(void)
{
	if(front!=rear)
		printf("element enqueued is :%d\n",queue[front++]);
	else
	{
		printf("queue empty!!\n");
		front=rear=0;
	}
}//end of dequeue

void display(void){
	int i;
	for(i=front;i<rear;i++)
		printf("%d\t",queue[i]);
	printf("\n");

}//end of display

void main()
{
	int c,item;
	while(1)
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
