/*
 * main.c
 *
 *  Created on: 09-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include 	"function_declaration.h"

static circular_anchor_p_t anchor = NULL;
circular_p_t item = NULL;
char chName[21],chName_To_Search[21],chNo_Data;

int main()
{
	Link_Init();
	while(1)
	{
		chNo_Data = Check_For_New_Entry();
		if(chNo_Data == 0)
		{
			Entry_Of_Data(item);
		}
		if(chNo_Data == 1)
		{
			break;
		}
	}
	printf("\nTerminating Program\n");
	Delete_All(anchor);
	return 0;
}


/*
 * Function name	:	Link_Init
 *
 * Description		:	use this function to initialize the head node
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Link_Init(void)
{
	anchor = Create_List("Circular_List");
}


/*
 * Function name	:	Entry_Of_Data
 *
 * Description		:	use this function to list the available options for data entry.
 *
 * Parameters		:	circular_p_t data_item -> pointer to the newly created item
 *
 * Returns			:	1 if user selects to quit 0 otherwise
 */
char Entry_Of_Data(circular_p_t data_item)
{
	int iNumber,iPlace;
	char chQuit = 0;
	circular_p_t after = NULL;
	circular_p_t before = NULL;

	while(1)
	{
		printf("Where do yo want to add\n"
				"1. At front?\n"
				"2. At tail?\n"
				"3. Anywhere else than front and tail?\n"
				"4. Delete an entry?\n"
				"5. chQuit:\n");
		scanf("%d",&iNumber);

		switch(iNumber)
		{
			case 1:	//at head

				printf("Ok at front\n");
				anchor =  Add_At_Head(anchor,data_item);
				Print_List(anchor);
				chQuit = 1;
				break;

			case 2:	//at tail

				printf("Ok at tail\n");
				anchor =  Add_At_Tail(anchor,data_item);
				Print_List(anchor);
				chQuit = 1;
				break;

			case 3:	//anywhere except head and tail

				printf("Ok after/before which entry?\n"
						"Please give the chName: ");
				scanf("%s",chName_To_Search);
				printf("For after %s press 1\n"
					   "For before %s press 2:",chName_To_Search,chName_To_Search);
				scanf("%d",&iPlace);
				switch(iPlace)
				{
					case 1:	//after that entry

						after = Search_By_Name(anchor, chName_To_Search);
						Add_After(after,data_item);
						Print_List(anchor);
						break;

					case 2: //before that entry

						before = Search_By_Name(anchor, chName_To_Search);
						Add_Before(data_item,before);
						Print_List(anchor);
						break;

					default:

						printf("Please provide the location\n");
						break;
				}
				chQuit = 1;
				break;

			case 4:

				Print_List(anchor);
				printf("Ok which entry to delete?\n"
						"Please give the chName: ");
				scanf("%s",chName_To_Search);
				Delete_Specific(anchor,chName_To_Search);
				Print_List(anchor);
				chQuit = 1;
				break;

			case 5:

				printf("Quiting...");
				chQuit = 1;
				break;

			default:

				printf("You have entered wrong position");
				chQuit = 1;
				break;
		}
		if(chQuit == 1)
			break;
	}
	return chQuit;
}


/*
 * Function name	:	Check_For_New_Entry
 *
 * Description		:	use this function to get a new entry from the user if user wants to add.
 *
 * Parameters		:	None
 *
 * Returns			:	1 if user selects to quit 0 if user entres the data 2 otherwise.
 */
char Check_For_New_Entry(void)
{
	char ch;
	printf("Do you want to add item? press y/n:");
	ch = getchar();
	if((ch == 'y') || (ch == 'Y'))
	{
		printf("Enter chName(20 characters only):");
		scanf("%s",chName);
		item = Create_Item(chName,sizeof(circular_t));
		return 0;
	}
	else if((ch == 'n') || (ch == 'N'))
	{
		return 1;
	}
	return 2;
}
