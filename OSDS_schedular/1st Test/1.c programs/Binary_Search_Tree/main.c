/*
 * main.c
 *
 *  Created on: 17-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>
#include 	"BST.h"

Tree_p Root = NULL;


int main()
{
	int iOption,iQuit = 0;
	int iSearch_Data,iHeight = 0,iInternal_Option;
	Tree_p Temp;
	time_t Start,End;
	double dDiff;

	while(1)
	{
		if(iQuit == 0)
		{
			printf("1. Insert a Data (not more than 1000) to notify the End of Entry give 1000 as data\n"
					"2. Search for a Specific Data\n"
					"3. Height of the Tree\n"
					"4. Traversal Display\n"
					"5. Quit:");
			scanf("%d",&iOption);
			switch(iOption)
			{
				case 1:

					while(1)
					{
						int iScan_Data;
						printf("Enter data to the tree: ");
						scanf("%d",&iScan_Data);
						if(iScan_Data != 1000)
							Insert_Data(iScan_Data,&Root);
						else
							break;
					}
					break;

				case 2:

					printf("Enter data to search in the tree");
					scanf("%d",&iSearch_Data);
					Temp = Search_Tree(iSearch_Data,Root);
					if(Temp == NULL)
						printf("Data does not exsist\n");
					else
						printf("Data %d exsist\n",iSearch_Data);
					break;

				case 3:

					iHeight = Height_Of_Tree(Root);
					printf("Height of the Tree is %d\n\n",iHeight);
					break;

				case 4:

					printf("Which traversal information you need?\n"
							"Please select below\n"
							"1. Pre-Order\n"
							"2. In-Oreder\n"
							"3. Post-Order\n"
							"4. Level-Order\n");
					scanf("%d",&iInternal_Option);
					switch(iInternal_Option)
					{
						case 1:

							printf("\nTree in PreOrder\n");
							time(&Start);
							List_In_PreOrder(Root);
							time(&End);
							dDiff = difftime(End,Start);
							printf("\nTime Taken is %f Seconds\n\n",dDiff);
							break;

						case 2:

							printf("\nTree in InOrder\n");
							time(&Start);
							In_Order(Root);
							time(&End);
							dDiff = difftime(End,Start);
							printf("\nTime Taken is %f Seconds\n\n",dDiff);
							break;

						case 3:

							printf("\nTree in PostOrder\n");
							time(&Start);
							List_In_PostOrder(Root);
							time(&End);
							dDiff = difftime(End,Start);
							printf("\nTime Taken is %f Seconds\n\n",dDiff);
							break;

						case 4:

							time(&Start);
							Print_Level_Order(Root);
							time(&End);
							dDiff = difftime(End,Start);
							printf("\nTime Taken is %f Seconds\n\n",dDiff);
							break;

						default:

							printf("Try again\n");
							break;
					}
					break;

				case 5:
					iQuit = 1;
					break;

				default:
					printf("Please provide input from the list\n");
					break;
			}
		}
		else
			break;
	}

	Destroy_Tree(Root);
	return 0;
}
