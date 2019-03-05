/*
 * main.c
 *
 *  Created on: 15-Jul-2015
 *      Author: tejas
 */

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<time.h>


int *iArray;
int iArray_Size,iData;

clock_t Start, End;

void 	Create_Array(int);									/*creates an array of size defined by the user*/
void 	Add_Data(int *);									/*adds data to the user defined array*/
int 	Search_List(int *,int);								/*searches the specific element in user defined array*/


int main()
{
	double time_taken;

	printf("Enter the size of the array:");
	scanf("%d",&iArray_Size);

	Create_Array(iArray_Size);								/*Now we have the size create the array of that size*/

	Add_Data(iArray);										/*Add data to the array this is also given by user*/

	printf("\nEnter the data to be search:");
	scanf("%d",&iData);

	Start = clock();										/*Start time of the function*/
	Search_List(iArray,iData);								/*Search the data given by user in the array*/
	End = clock() - Start;									/*End time of the function*/
	time_taken = ((double)End)/CLOCKS_PER_SEC;				/*Actual time taken by the function*/

	printf("\nTime taken to search is %f seconds\n\n\n",time_taken);

	free(iArray);											/*Delete the array before terminating*/
	return 0;
}


/*
 * Function name	:	Create_Array
 *
 * Description		:	creates an array with the size specified by user
 *
 * Parameters		:	int iSize -> size given by the user.
 *
 * Returns			:	None
 *
 */
void Create_Array(int iSize)
{
	iArray = (int *)malloc(iSize*(sizeof(int)));
	if(iArray == NULL)
	{
		exit(EXIT_FAILURE);
	}
}


/*
 * Function name	:	Add_Data
 *
 * Description		:	Adds data to the user defined array given by user.
 *
 * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
 *
 * Returns			:	None
 *
 */
void Add_Data(int *iPtr)
{
	int i = 0;												/*local variable for the loop*/
	printf("Please enter %d values in ascending order in the array:\n",iArray_Size);
	while(i < iArray_Size)
	{
		scanf("%d",iPtr+i);
		i++;
	}
}


/*
 * Function name	:	Search_List
 *
 * Description		:	Searches in the array for the specific data given by user.
 *
 * Parameters		:	int iSearch_Data -> Data provided by user for search
 * 					:	int *iPtr ->  pointer to the array defined by user earlier
 *
 * Returns			:	None
 *
 */

int Search_List(int *iPtr,int iSearch_Data)
{
	int iBreak = 0;												/*local variable for the loop*/
	int iLow = 0,iHigh = iArray_Size - 1,iMid;
	while(iLow <= iHigh)
	{
		iMid = (iLow + iHigh)/2;

		if(*(iPtr+iMid) < iSearch_Data)
		{
			iLow = iMid++;
		}
		else if(*(iPtr+iMid) == iSearch_Data)
		{
			iBreak = 1;
			break;
		}
		else if(*(iPtr+iMid) > iSearch_Data)
		{
			iHigh = iMid--;
		}
	}
	if(iBreak == 0)
	{
		printf("\nThere is no such entry\n\n\n");
		return -1;
	}
	else
	{
		printf("%d is found at %d\n\n\n",iSearch_Data,iMid+1);
		return iMid;
	}
}


/* use TIMEFORMAT="" time ./filename
 *
 * to compile the program. for getting ram information and cpu usage
 */
