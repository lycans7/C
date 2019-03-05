/*
 * main.c
 *
 *  Created on: 16-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>

#define 	MAX		100

clock_t Start,End;
int iArray[MAX];
int iArray_Size;


int 		Comp_Func (const void *, const void *);		/*comapres the values for qsort function.*/
void 		Add_Data(void);							/*adds data to the user defined array*/
void 		Print_Array(void);							/*Prints the elements of the array*/

int main()
{
	double dTime_Taken;

	printf("Enter the size of the array:");
	scanf("%d",&iArray_Size);

//	Create_Array(iArray_Size);								/*Now we have the size create the array of that size*/

	Add_Data();												/*Add data to the array this is also given by user*/

	Print_Array();											/*Prints the elements of the array*/

	Start = clock();										/*Start time of the function*/
	qsort(iArray,iArray_Size,sizeof(int),Comp_Func);		/*Sort the data given by user in the array*/
	End = clock() - Start;									/*End time of the function*/
	dTime_Taken = ((double)End)/CLOCKS_PER_SEC;				/*Actual time taken by the function*/

	Print_Array();

	printf("\nTime taken to sort is %f seconds\n\n\n",dTime_Taken);

//	free(iArray);											/*Delete the array before terminating*/
	return 0;
}


/*
 * Function name	:	Comp_Func
 *
 * Description		:	Compares two values for the qsort function.
 *
 * Parameters		:	const void * a -> reference to the passed value
 * 						const void * b -> reference to the passed value
 *
 * Returns			:	comaprision between two integers
 *
 */
int Comp_Func (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
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
void Add_Data(void)
{
	int iLocal = 0;								  /*local variable for the loop*/
	printf("Enter %d values to the list:\n",iArray_Size);
	while(iLocal < iArray_Size)
	{
		scanf("%d",&iArray[iLocal]);
		iLocal++;
	}
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
void Print_Array(void)
{
	int iOuter_Loop;
	for(iOuter_Loop=0;iOuter_Loop < iArray_Size; iOuter_Loop++)
	{
		printf("%d. %d\n",iOuter_Loop+1,iArray[iOuter_Loop]);
	}
	printf("\n");
}
