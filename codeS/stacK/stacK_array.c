/*****************************************************************************************
*                                     stacK  using array                                 *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void push();
void pop();
void display();
int a[20],top;

void main()
{
	char ch;
	do
	{
		printf("1. Push the data in the Stack\n");
		printf("2. Pop the data from the Stack\n");
		printf("3. Display\n");
		printf("4. Exit\n");

		printf("Enter the Choice :: ");
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
				display();
				break;
			case '4':
				exit(0);
		}
	}while(1);       
}
void push()
{
	printf("\nEnter the Data You want to Push :: ");
	scanf("%d",&a[top]);

	top+=1;
	if(top==20)
		printf("Stack overflaw\n");
	else
		return;
}
void pop()
{
	printf("Popped Data is :: %d\n",a[top-1]);
	top-=1;
	if(top==0)
		printf("Stack Underflaw\n");
	else
		return;
}
void display()
{
	int i;
	if(top!=0)
	{
	       	for(i=top-1;i>=0;i--)
		{
			printf("All the Data Elements in the Stack Are :: %d\n",a[i]);
		}
	}
	else
		printf("Stack is Empty !!!! \n");

}

