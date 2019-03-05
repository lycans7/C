/*
 * link_functions.c
 *
 *  Created on: 09-Jul-2015
 *      Author: tejas
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "function_declaration.h"

static int iExist_Only_One = 1;

/*
 * Function name	:	Create_List
 *
 * Description		:	use this function to create a head node with user given value.
 * 						points to itself in fwd link as well as in bked link.
 *
 * Parameters		:	const char *name -> name of the entry
 *
 * Returns			:	pointer to the created head node
 *
 */

circular_anchor_p_t Create_List(const char *name)
{
	circular_anchor_p_t list = NULL;

	list = (circular_anchor_p_t)malloc(sizeof(circular_anchor_t));
	if(list != NULL)
	{
		list->flink = list;
		list->blink = list;
		list->name = cover_new_str_if(name);
	}
	return list;
}

/*
 * Function name	:	Create_Item
 *
 * Description		:	use this function to create a node with user given value and size.
 * 						points to itself in fwd link as well as in bked link.
 *
 * Parameters		:	const char *name -> name of the entry
 * 						size_t size -> size of the element which is created
 *
 * Returns			:	pointer to the created node
 *
 */

circular_p_t Create_Item(const char *name,size_t size)
{
	circular_p_t item = (circular_p_t)Cover_Malloc(size);

	item->flink = item;
	item->blink = item;
	item->name = cover_new_str_if(name);

	return item;
}


/*
 * Function name	:	Add_Before
 *
 * Description		:	use this function to add a node before any node specified by user in the list
 *
 * Parameters		:	circular_p_t item -> newly created item which we want to add
 * 						circular_p_t before -> pointer to the entry before which we want to add the item
 *
 * Returns			:	pointer to the added node
 *
 */
circular_p_t Add_Before(circular_p_t item,circular_p_t before)
{
	int iExist;
	circular_p_t search = NULL;

	search = before->flink;

	while(search != before)
	{
		iExist = Item_Exist(item);
		if(iExist == 0)
		{
			search = search->flink;
		}
		else
		{
//			iExist = 1;
			break;
		}
	}
	if(iExist == 0)
	{
		before->blink->flink = item;
		item->flink = before;
		item->blink = before->blink;
		before->blink = item;
		return item;
	}
	else
		return NULL;
}


/*
 * Function name	:	Add_After
 *
 * Description		:	use this function to add a node after any node specified by user in the list
 *
 * Parameters		:	circular_p_t after -> pointer to the entry after which we want to add the item
 * 						circular_p_t item -> newly created item which we want to add
 *
 * Returns			:	pointer to the added node
 *
 */
circular_p_t Add_After(circular_p_t after,circular_p_t item)
{
	item->flink = after->flink;
	after->flink = item;
	item->blink = after;
//	after->blink = item;
	return item;
}


/*
 * Function name	:	Add_At_Head
 *
 * Description		:	use this function to add a node to the head in the list
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head
 * 						circular_p_t item -> newly created item which we want to add
 *
 * Returns			:	pointer to the head node
 *
 */
circular_p_t Add_At_Head(circular_anchor_p_t list,circular_p_t item)
{
	circular_p_t ptr = NULL;

	item->flink = list;
	item->blink = list->blink;
	if(iExist_Only_One == 1)
	{
		list->flink = item;
		iExist_Only_One = 2;
	}
	else
		list->blink->flink = item;
	list->blink = item;
	ptr = item;
	item = list;
	list = ptr;
	return list;
}


/*
 * Function name	:	Add_At_Tail
 *
 * Description		:	use this function to add a node to the tail in the list
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head
 * 						circular_p_t item -> newly created item which we want to add
 *
 * Returns			:	pointer to the head node
 *
 */
circular_p_t Add_At_Tail(circular_anchor_p_t list,circular_p_t item)
{
	item->flink = list;
	item->blink = list->blink;
	list->blink->flink = item;
	list->blink = item;
	if(iExist_Only_One == 1)
		iExist_Only_One = 2;
	return list;
}


/*
 * Function name	:	Remove_From_List
 *
 * Description		:	use this function to remove the entry from the list not actually removing just making
 * 						it isolated so that we can delete that node without any errors.
 *
 * Parameters		:	circular_p_t item -> pointer to the item which we want to remove from the list
 *
 * Returns			:	pointer to the item node after or before which we have removed the entry
 *
 */
circular_p_t Remove_From_List(circular_p_t item)
{
    item->blink->flink = item->flink;
    item->flink->blink = item->blink;
    item->flink = item;
    item->blink = item;
    return item;
}


/*
 * Function name	:	Delete_From_Tail
 *
 * Description		:	use this function to delete the entry from the tail of the list this function actually
 * 						deletes the entry from the tail using the Remove_From_List() function.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head.
 *
 * Returns			:	NULL
 *
 */
circular_p_t Delete_From_Tail(circular_anchor_p_t list)
{
	circular_p_t ptr;
	ptr = list->blink;
    list->blink->blink->flink = list;
    list->blink = list->blink->blink;
    ptr->flink = ptr;
    ptr->blink = ptr;

    Delete_From_List(ptr);

    return NULL;
}


/*
 * Function name	:	Delete_From_Head
 *
 * Description		:	use this function to delete the entry from the head of the list this function actually
 * 						deletes the entry from the tail using the Remove_From_List() function.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head.
 *
 * Returns			:	pointer to the new head node of the list
 */
circular_p_t Delete_From_Head(circular_anchor_p_t list)
{
	circular_p_t ptr;
	ptr = list->flink;
    list->flink->blink = list->blink;
    list->blink->flink = list->flink;
    list->flink = list;
    list->blink = list;

    Delete_From_List(list);

    return ptr;
}


/*
 * Function name	:	Delete_From_List
 *
 * Description		:	use this function to delete the entry Delete_From_Tail() and  Delete_From_Head()
 * 						functions internally uses this function to delete the entry.
 *
 * Parameters		:	circular_p_t item -> pointer to the item which we want to delete.
 *
 * Returns			:	NULL
 */

circular_p_t Delete_From_List(circular_p_t item)
{
    Remove_From_List(item);
    Cover_Free(item->name);
    Cover_Free(item);
    return NULL;
}


/*
 * Function name	:	Delete_Specific
 *
 * Description		:	use this function to delete specific entry from the list specified by its name.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head
 * 						char *name -> name of the entry which we want to delete.
 *
 * Returns			:	None
 */

void Delete_Specific(circular_anchor_p_t list,char *name)
{
	circular_p_t ptr = NULL;
	ptr = Search_By_Name(list, name);
	Delete_From_List(ptr);
}


/*
 * Function name	:	Delete_All
 *
 * Description		:	use this function to delete all the entries in the list.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head
 *
 * Returns			:	None
 */

void Delete_All(circular_anchor_p_t list)
{
	circular_p_t ptr = NULL;
	ptr = list->flink;
	while(ptr != list)
	{
		Delete_From_List(ptr);
		ptr = list->flink;
	}
	Delete_From_List(list);
}


/*
 * Function name	:	Search_In_List
 *
 * Description		:	use this function to search  all the entries in the list by its pointer.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head
 *
 * Returns			:	1 if entry exist else 0
 */

int Search_In_List(circular_anchor_p_t list)
{
	int iExist;

	circular_p_t search = NULL;

	search = list->blink;
	while(search != list)
	{
		iExist = Item_Exist(search);
		if(iExist == 0)
		{
			search = search->blink;
		}
		else
		{
			break;
		}
	}

	return iExist;
}


/*
 * Function name	:	Item_Exist
 *
 * Description		:	use this function to check for the item's existance in the list.
 *
 * Parameters		:	circular_p_t item -> pointer to the item which is being searched.
 *
 * Returns			:	1 if entry exist else 0
 */

int Item_Exist(circular_p_t item)
{
	int iExist;

	iExist = (item->flink == item ? 0 : 1);

	return iExist;
}


/*
 * Function name	:	Cover_Malloc
 *
 * Description		:	use this function to assign memory safely.
 *
 * Parameters		:	size_t size -> size for the memory allocation.
 *
 * Returns			:	returns the pointer of the allocated memory
 */

void *Cover_Malloc(size_t size)
{
	void *mem = malloc(size);
	if(mem == NULL && size>0)
		abort();
	return mem;
}


/*
 * Function name	:	Cover_Free
 *
 * Description		:	use this function to free the memory safely.
 *
 * Parameters		:	void *mem -> pointer to the memory which needs to be free
 *
 * Returns			:	None
 */

void Cover_Free(void *mem)
{
	if(mem != NULL)
		free(mem);
}


/*
 * Function name	:	Search_By_Name
 *
 * Description		:	use this function to search the entry by its name.
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head node
 * 						char *name -> name of the entry we need to search
 *
 * Returns			:	returns the pointer to the found item if item is found otherwise NULL
 */

circular_p_t Search_By_Name(circular_anchor_p_t list, char *name)
{
	int iExist;
	circular_p_t item = NULL;
	item = list->flink;

	while(item != list)
	{

		if(strcmp(name,item->name) != 0)
		{
			iExist = 0;
			item = item->flink;
		}
		else
		{
			iExist = 1;
			break;
		}
	}

	if(iExist == 1)
		return item;
	else
		return NULL;
}



/*
 * Function name	:	Print_List
 *
 * Description		:	use this function to print all the entries in the list
 *
 * Parameters		:	circular_anchor_p_t list -> pointer to the head node
 *
 * Returns			:	None
 */
void Print_List(circular_anchor_p_t list)
{
	circular_p_t print = NULL;

	print = list->flink;

	printf("List entry is \"%s\"\n",list->name);

	while(print != list)
	{
		printf("List entry is \"%s\"\n",print->name);
		print = print->flink;
	}
}
