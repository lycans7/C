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
}*root;
 
void insertNode(struct node *q, int data)
{
    if(q == NULL)													// First node
	{
        struct node *ptr = (struct node*)malloc(sizeof(struct node));
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
        root = ptr;
        return;
    }
    else if(data < q->data && q->left != NULL)						// search for the position
	{
        q = q->left;
        insertNode(q,data);
    }
    else if(data > q->data && q->right != NULL) 
	{
        q = q->right;
        insertNode(q,data);
    }
    else if(q->left == NULL && data < q->data) 
	{
        struct node *ptr = (struct node*)malloc(sizeof(struct node));
        ptr->data = data;
        ptr->right = NULL;
        ptr->left = NULL;
        q->left = ptr;
        return;
    }
    else if(q->right == NULL && data > q->data) 
	{
        struct node *ptr = (struct node*)malloc(sizeof(struct node));
        ptr->data = data;
        ptr->right = NULL;
        ptr->left = NULL;
        q->right = ptr;
        return;
    }
}
 
void inOrder(struct node *q) 
{
    if(q != NULL) 
	{
        inOrder(q->left);
        printf("%d\t",q->data);
        inOrder(q->right);
    }
}
 
void preOrder(struct node *q) 
{
    if(q != NULL) 
	{
        printf("%d\t",q->data);
        preOrder(q->left);
        preOrder(q->right);
    }
}
 
void postOrder(struct node *q) 
{
    if(q != NULL) 
	{
        postOrder(q->left);
        postOrder(q->right);
        printf("%d\t",q->data);
    }
}
 
void main() 
{
    int d,i,n,ch;
    printf("Enter number of nodes in Binary Searcg Tree :: ");
    scanf("%d",&n);
    while(1)
    {
    printf("1. Create Binary Search Tree\n2. Inorder traversal\n3. Preorder traversal\n4. Postorder traversal\nEnter the choice :: ");
    scanf("%d",&ch);
    
    switch(ch)
    {
    	case 1:
    		for(i=0;i<n;i++) 
			{
        		printf("Enter node to BST :: ");
        		scanf("%d",&d);
        		insertNode(root,d);
    		}
    		break;
		case 2:
			printf("In-order traversal is :: ");
			inOrder(root);
			printf("\n");
			break;
		case 3:
			printf("Pre-order traversal is :: ");
			preOrder(root);
			printf("\n");
			break;
		case 4:
			printf("Post-order traversal is :: ");
			postOrder(root);
			printf("\n");
			break;
		default:
			printf("Invalid choice..\n");
			exit(1);
	}
	}
 }
