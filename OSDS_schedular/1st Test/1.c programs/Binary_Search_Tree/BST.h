/*
 * BST.h
 *
 *  Created on: 17-Jul-2015
 *      Author: tejas
 */

#ifndef BST_H_
#define BST_H_


typedef struct node
{
	int iData;
	struct node *Left;
	struct node *Right;
}Tree_t,*Tree_p;



void		Destroy_Tree(Tree_p);				/*Delete the tree*/
void		Insert_Data(int, Tree_p*);			/*Insert data to the tree*/
Tree_p		Search_Tree(int,Tree_p);			/*Search in the tree for specific data*/
int			Height_Of_Tree(Tree_p);				/*Get us the height of the tree*/
void 		Print_Level_Order(Tree_p);			/*prints the level order information*/
void 		Print_Given_Level(Tree_p, int);		/*prints particular level recursivaley till the end*/
void 		List_In_PostOrder(Tree_p);			/*prints the list in post order traversal*/
void 		In_Order(Tree_p);					/*prints the list in in order traversal*/
void 		List_In_PreOrder(Tree_p );			/*prints the list in pre order traversal*/


#endif /* BST_H_ */
