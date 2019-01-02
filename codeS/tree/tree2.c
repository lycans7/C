/*****************************************************************************************
*                            implementation of binary tree                               *
*                                                                                        *
*                              KartiK : kartikdb@cdac.in                                 *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct node
{
	struct node *left;
	int data;
	struct node *right;
}*root,*ptr,*parent;

void create(int info)
{
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr -> data = info;
	ptr -> left = NULL;
	ptr -> right = NULL;
	
	if(root == NULL)
	{
		root = ptr;
		return;
	}
	else
	{
		parent = root;
		if(info < parent -> data)
		{
			while(parent -> left != NULL)
				parent = parent -> left;
			if(info < parent -> data)
				parent -> left = ptr;
			else
				parent -> right = ptr;
			return;
		}
		else
		{
			while(parent -> right != NULL)
				parent = parent -> right;
			if(info < parent -> data)
				parent -> left = ptr;
			else
				parent
				 -> right = ptr;				
			return;
		}
	}
	
}
void inorder(struct node *q)
{
	if(q != NULL)
	{
		inorder(q -> left);
		printf("%d\t",q -> data);
		inorder(q -> right);
	}
}
void preorder(struct node *q)
{
	if(q != NULL)
	{
		printf("%d\t",q -> data);
		preorder(q -> left);
		preorder(q -> right);
	}
}
void postorder(struct node *q)
{
	if(q != NULL)
	{
		postorder(q -> left);
		postorder(q -> right);
		printf("%d\t",q -> data);
	}
}
main()
{
	int ch,info;
	while(2)
	{
		printf("1. create\n2. inroder\n3. preorder\n4. postorder\nEmter the choice :: ");
		scanf("%d",&ch);
		switch(ch)
		{	
			case 1:
				printf("Enter the value to the node :: ");
				scanf("%d",&info);
				create(info);
				break;
			case 2:
				printf("In-order traversal is :: ");
				inorder(root);
				printf("\n");
				break;
			case 3:
				printf("Pre-order traversal is :: ");
				preorder(root);
				printf("\n");
				break;
			case 4:
				printf("Post-order traversal is :: ");
				postorder(root);
				printf("\n");
				break;
			default:
				printf("Invalid choice \n");
				exit(1);
	}
	}
}
