/*
 * main.c
 *
 *  Created on: 15-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include	<time.h>
#include 	<stdlib.h>


void		Create_Array(int);							/*creates an array of size defined by the user*/
void 		Add_Data(int *);							/*adds data to the user defined array*/
void		Bubble_Sort(int *);							/*sort the array using bubble sort method*/
void 		Print_Array(int *);							/*Prints the elements of the array*/


int *iArray;
int iArray_Size;

clock_t Start,End;

int main()
{
	double time_taken;

	printf("Enter the size of the array:");
	scanf("%d",&iArray_Size);

	Create_Array(iArray_Size);								/*Now we have the size create the array of that size*/

	Add_Data(iArray);										/*Add data to the array this is also given by user*/

	Print_Array(iArray);											/*Prints the elements of the array*/

	Start = clock();										/*Start time of the function*/
	Bubble_Sort(iArray);									/*Sort the data given by user in the array*/
	End = clock() - Start;									/*End time of the function*/
	time_taken = ((double)End)/CLOCKS_PER_SEC;				/*Actual time taken by the function*/

	printf("\nTime taken to sort is %f seconds\n\n\n",time_taken);

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
	printf("Enter %d values in descending order to the list:\n",iArray_Size);
	while(i < iArray_Size)
	{
		scanf("%d",iPtr+i);
		i++;
	}
}


/*
 * Function name	:	Bubble_Sort
 *
 * Description		:	use this function to sort the data of the array using Bubble sort method
 *
 * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
 *
 * Returns			:	None
 *
 */
void Bubble_Sort(int *iPtr)
{
	int iOuter_Loop,iInner_Loop,iTemp;
	for(iOuter_Loop=0;iOuter_Loop < (iArray_Size-1);iOuter_Loop++)
	{
		for(iInner_Loop=0;iInner_Loop < (iArray_Size - iOuter_Loop -1);iInner_Loop++)
		{
			if(*(iPtr+iInner_Loop) > *(iPtr+iInner_Loop+1))
			{
				iTemp = *(iPtr+iInner_Loop);
				*(iPtr+iInner_Loop) = *(iPtr+iInner_Loop+1);
				*(iPtr+iInner_Loop+1) = iTemp;
			}
		}
	}
	Print_Array(iPtr);
}


/*
 * Function name	:	Print_Array
 *
 * Description		:	use this function to print the array as it is
 *
 * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
 *
 * Returns			:	None
 *
 */
void Print_Array(int *iPtr)
{
	int iOuter_Loop;
	for(iOuter_Loop=0;iOuter_Loop < iArray_Size; iOuter_Loop++)
	{
		printf("%d. %d\n",iOuter_Loop,*(iPtr+iOuter_Loop));
	}
	printf("\n");
}
