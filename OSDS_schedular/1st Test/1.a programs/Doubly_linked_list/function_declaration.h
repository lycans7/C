/*
 * function_declaration.h
 *
 *  Created on: 09-Jul-2015
 *      Author: tejas
 */

#ifndef FUNCTION_DECLARATION_H_
#define FUNCTION_DECLARATION_H_


#define cover_cardinality(arr)	(sizeof(arr)/sizeof(*(arr)))
#define cover_new(type)			((type*)Cover_Malloc(sizeof(type)))
#define cover_new_str(str)		(strcpy((char*)Cover_Malloc(strlen(str)+1),str))
#define cover_new_str_if(str)	((str) == NULL ? NULL : cover_new_str(str))

typedef struct node
{
	struct node *flink;
	struct node *blink;
	char *name;
}circular_t,*circular_p_t;

typedef circular_t circular_anchor_t,*circular_anchor_p_t;

circular_anchor_p_t 	Create_List(const char *);						/*creates a head node which points to it self*/
circular_p_t 			Create_Item(const char *,size_t);				/*creates an item with fwd and bkwd link pointing itself*/
circular_p_t 			Add_Before(circular_p_t,circular_p_t);			/*add user given value before specified value*/
circular_p_t 			Add_After(circular_p_t,circular_p_t);			/*add user given value after specified value*/
circular_p_t 			Add_At_Head(circular_anchor_p_t,circular_p_t);	/*adds the user given value at head*/
circular_p_t 			Add_At_Tail(circular_anchor_p_t,circular_p_t);	/*adds the user given value at end*/

circular_p_t 			Remove_From_List(circular_p_t);					/*remove the entry name from the list */
circular_p_t 			Delete_From_List(circular_p_t);					/*delete an entry from the list*/
circular_p_t 			Delete_From_Tail(circular_anchor_p_t);			/*delete an entry from tail*/
circular_p_t 			Delete_From_Head(circular_anchor_p_t);			/*delete an entry from the head*/
void 					Delete_Specific(circular_anchor_p_t,char *);	/*delete a specific entry from the list*/
void 					Delete_All(circular_anchor_p_t);				/*delete all entries from the list*/

int 					Search_In_List(circular_anchor_p_t);			/*searches for specific entry*/
circular_p_t 			Search_By_Name(circular_anchor_p_t, char *);	/*searches for specific entry in list by its name*/

void 					Link_Init(void);								/*allocates space for the structure*/

void 	*				Cover_Malloc(size_t);							/*covers malloc from unwanted errors*/
void 					Cover_Free(void*);								/*covers free from unwanted errors*/

int 					Item_Exist(circular_p_t);						/*checks if the item is in the list or not*/

char 					Entry_Of_Data(circular_p_t data_item);			/*location of data entry in linked list is asked*/
char 					Check_For_New_Entry(void);						/*if user has given a new entry then create an item*/

void 					Print_List(circular_anchor_p_t);				/*prints the list*/

#endif /* FUNCTION_DECLARATION_H_ */
