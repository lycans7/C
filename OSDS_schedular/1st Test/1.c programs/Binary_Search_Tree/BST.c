/*
 * BST.c
 *
 *  Created on: 17-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>
#include 	"BST.h"


/*
 * Function name	:	Destroy_Tree
 *
 * Description		:	use this function to destroy the Tree
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void Destroy_Tree(Tree_p Leaf)
{
	if(Leaf != 0)
	{
		Destroy_Tree(Leaf->Left);
		Destroy_Tree(Leaf->Right);
		free(Leaf);
	}
}


/*
 * Function name	:	Insert_Data
 *
 * Description		:	use this function to insert an element to the tree
 *
 * Parameters		:	int iKey ->	data to be entered in the tree
 * 						Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void Insert_Data(int iKey, Tree_p* Leaf)
{
	if( *Leaf == 0 )
	{
		*Leaf = (Tree_p) malloc(sizeof(Tree_t));
		(*Leaf)->iData = iKey;
		/* initialize the children to null */
		(*Leaf)->Left = NULL;
		(*Leaf)->Right = NULL;
	}
	else if(iKey < (*Leaf)->iData)
	{
		Insert_Data( iKey, &(*Leaf)->Left );
	}
	else if(iKey > (*Leaf)->iData)
	{
		Insert_Data( iKey, &(*Leaf)->Right );
	}
}


Tree_p Search_Tree(int iKey,Tree_p Leaf)
{
	if( Leaf != 0 )
	  {
	      if(iKey == Leaf->iData)
	      {
	          return Leaf;
	      }
	      else if(iKey < Leaf->iData)
	      {
	          return Search_Tree(iKey, Leaf->Left);
	      }
	      else
	      {
	          return Search_Tree(iKey, Leaf->Right);
	      }
	  }
	  else
		  return NULL;
}


/*
 * Function name	:	Height_Of_Tree
 *
 * Description		:	use this function to get the height of the tree
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
int Height_Of_Tree(Tree_p Leaf)
{
	if (Leaf==NULL)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int iLheight = Height_Of_Tree(Leaf->Left);
		int iRheight = Height_Of_Tree(Leaf->Right);

		/* use the larger one */
		if (iLheight > iRheight)
			return(iLheight+1);
		else
			return(iRheight+1);
	}
}


/*
 * Function name	:	Print_Level_Order
 *
 * Description		:	use this function to print the tree in level order traversal
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void Print_Level_Order(Tree_p Leaf)
{
	int iHeight = Height_Of_Tree(Leaf);
	int iLoop;
	printf("Printing the Level order traversal of a tree\n"
			"of Height %d\n",iHeight);
	for(iLoop=1; iLoop<=iHeight; iLoop++)
		Print_Given_Level(Leaf, iLoop);
}


/*
 * Function name	:	Print_Given_Level
 *
 * Description		:	use this function to actually print the level order traversal
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 * 						int iLevel -> how deep you have to search
 *
 * Returns			:	None
 */
void Print_Given_Level(Tree_p Leaf, int iLevel)
{
	if(Leaf == NULL)
		return;

	if(iLevel == 1)
		printf("%d, ", Leaf->iData);
	else if (iLevel > 1)
	{
		Print_Given_Level(Leaf->Left, iLevel-1);
		Print_Given_Level(Leaf->Right, iLevel-1);
	}
}


/*
 * Function name	:	List_In_PreOrder
 *
 * Description		:	use this function to print the tree in Pre order traversal recursivaley
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void List_In_PreOrder(Tree_p Leaf)
{
	if(Leaf != NULL)
	{
        printf("%d, ", Leaf->iData);
        List_In_PreOrder(Leaf->Left);
        List_In_PreOrder(Leaf->Right);
    }
}


/*
 * Function name	:	In_Order
 *
 * Description		:	use this function to print the tree in In-order traversal recursivaley
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void In_Order(Tree_p Leaf)
{
   if (Leaf != NULL)
   {
	  In_Order(Leaf->Left);
      printf("%d, ", Leaf->iData);
      In_Order(Leaf->Right);
   }
}


/*
 * Function name	:	List_In_PostOrder
 *
 * Description		:	use this function to print the tree in Post-order traversal recursivaley
 *
 * Parameters		:	Tree_p Leaf -> Pointer to the root of the tree
 *
 * Returns			:	None
 */
void List_In_PostOrder(Tree_p Leaf)
{
	if(Leaf != NULL)
	{
		List_In_PostOrder(Leaf->Left);
		List_In_PostOrder(Leaf->Right);
        printf("%d, ", Leaf->iData);
    }
}


//30, 20, 40, 15, 25, 35, 45, 10, 18, 5
