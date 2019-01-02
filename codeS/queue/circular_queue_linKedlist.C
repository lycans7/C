/*****************************************************************************************
*                            circular queue using linKed list                            *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
typedef struct queue{
	int data;
	struct queue *nxt;
} queue;
queue *front,*rear;

void enqueue(int item){
	queue *new;
	new=malloc(sizeof(queue));
	new->data=item;
	if(front==NULL){
		front=new;
		rear=front;
	}
	else{   					// circular queue
		rear->nxt=new;
		rear=new;
	}
	new->nxt=front;
}//end of enqueue

void dequeue(void){
	queue *temp=front;
	if(front!=NULL && front!=rear){
		printf("element dequeued is :%d\n",front->data);
		front=front->nxt;
		rear->nxt=front;
		free(temp);
	}
	else if(front!=NULL && front==rear){
		printf("element dequeued is :%d\n",front->data);
		free(temp);
		front=rear=NULL;
	}
	else
		printf("queue empty!!\n");
}//end of dequeue

void display(void){
	queue *temp=front;
	if(front!=NULL)
	{
		do{
			printf("%d\t",temp->data);
			temp=temp->nxt;
		}while(temp!=front);
		printf("\n");
	}
	else
		printf("queue empty!!\n");

}//end of display

			////*****main function****/////
void main(){
	int c=1,item;	clrscr();
	while(c){
		printf("1:enqueue\n2:dequeue\n3:display\n0:exit\nchoose the option:");
		scanf("%d",&c);
		switch(c){
			case 1:printf("enter the element:");
				 scanf("%d",&item);
				enqueue(item);
				 break;
			case 2:dequeue();
				 break;
			case 3:display();
				 break;
			case 0:break;
			default:printf("invalid option\n");
		}//end of switch
	}//end of while
	getch();
}//end of main
