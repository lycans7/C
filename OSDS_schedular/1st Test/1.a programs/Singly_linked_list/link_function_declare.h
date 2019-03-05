/*
 * link_function_declare.h
 *
 *  Created on: 08-Jul-2015
 *      Author: tejas
 */

#ifndef LINK_FUNCTION_DECLARE_H_
#define LINK_FUNCTION_DECLARE_H_

struct node
{
	int iData;													/*Data to be handled at particular node*/
	struct node *next;											/*next pointer points to the next element in the list*/
};


struct node	* 	Create_Node(int);								/*used to create the head node for linked list*/
int 			Push(struct node**);							/*add the values entered to the head*/
void 			Print_List(struct node **);						/*prints the entries in the list*/
int 			Add_At_Tail(struct node **);					/*add the value at the end of the list*/
void 			Recursive_Reverse(struct node**);				/*reversing the linked list*/
void 			Destroy_List(struct node **);					/*delete the linked list*/
int 			Length(struct node*);							/*get us the length of the linked list*/

#endif /* LINK_FUNCTION_DECLARE_H_ */
