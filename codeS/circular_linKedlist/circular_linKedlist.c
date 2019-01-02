/****************************************************
*													*
*	   division of linKed list into two parts       *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<stdlib.h>
					// division of linked list into two parts
typedef struct cList{
	struct cList *nxt;
	int data;
} cList;
cList *start,*last;
int tot=0;

void create(){
	cList *new;
	int i=0,n;
	printf("enter the num of entries:");
	scanf("%d",&n);
	while(i<n){
		new=malloc(sizeof(cList));
		printf("enter number:");
		scanf("%d",&new->data);
		new->nxt=start;
		if(start==NULL){
			start=new;
			last=start;
		}//end of if
		else{
			last->nxt=new;
			last=new;
		}//end of else
		i++;
	}//end of while
	tot=tot+n;
}//end of create

void displayAll(cList *half){
	cList *temp;
	temp=half;
	do{
		printf("\t%d",temp->data);
		temp=temp->nxt;
	}while(temp!=half);
	printf("\n");
}//end of displayAll

void twoHalves(){
	cList *tor=start,*hare=start,*temp;
	while(hare->nxt!=start){
		hare=hare->nxt;
		if(hare->nxt==start)
			break;
		else
			hare=hare->nxt;
		tor=tor->nxt;
	}
	hare->nxt=tor->nxt;
	tor->nxt=start;
	displayAll(tor->nxt);
	printf("\n");
	displayAll(hare->nxt);
}//end of twoHalves


int main(){
	int c,i;
	start=NULL;
	while(c){
		printf("choose the option:\n1:create\n2:split into two\n3:display all\n0:exit\n");
		scanf("%d",&c);
		switch(c){
			case 1:create();
				 break;
			case 2:twoHalves();
				 break;
			case 3:displayAll(start);
			case 0:break;
			default:printf("Invalid option\n");
				break;
		}//end of switch
	}//end of while
}//end of main


