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

#define 	MAX		100

//void		Create_Array(int);							/*creates an array of size defined by the user*/
void 		Add_Data(void);								/*adds data to the user defined array*/
void		Radix_Sort(void);							/*sort the array using bubble sort method*/
//int 		Get_Max(int *);								/*gives the maximum number out of the
//																	array with corresponding Radix*/
void 		Print_Array(void);							/*Prints the elements of the array*/
//void		Do_Sort();									/*Do the sorting for 1 time when called*/


int iArray[MAX];
int iArray_Size;

clock_t Start,End;

int main()
{
	double time_taken;

	printf("Enter the size of the array:");
	scanf("%d",&iArray_Size);

//	Create_Array(iArray_Size);								/*Now we have the size create the array of that size*/

	Add_Data();										/*Add data to the array this is also given by user*/

	Print_Array();											/*Prints the elements of the array*/

	Start = clock();										/*Start time of the function*/
	Radix_Sort();									/*Sort the data given by user in the array*/
	End = clock() - Start;									/*End time of the function*/
	time_taken = ((double)End)/CLOCKS_PER_SEC;				/*Actual time taken by the function*/

	Print_Array();

	printf("\nTime taken to sort is %f seconds\n\n\n",time_taken);

//	free(iArray);											/*Delete the array before terminating*/
	return 0;
}



///*
// * Function name	:	Create_Array
// *
// * Description		:	creates an array with the size specified by user
// *
// * Parameters		:	int iSize -> size given by the user.
// *
// * Returns			:	None
// *
// */
//void Create_Array(int iSize)
//{
//	iArray = (int *)malloc(iSize*(sizeof(int)));
//	if(iArray == NULL)
//	{
//		exit(EXIT_FAILURE);
//	}
//}


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
	int i = 0;												/*local variable for the loop*/
	printf("Enter %d values to the array:\n",iArray_Size);
	while(i < iArray_Size)
	{
		scanf("%d",&iArray[i]);
		i++;
	}
}


/*
 * Function name	:	Radix_Sort
 *
 * Description		:	use this function to sort the data of the array using Bubble sort method
 *
 * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
 *
 * Returns			:	None
 *
 */
void Radix_Sort(void)
{
/*	int iBucket[10][20]={{0,0}},iBuck_Count[10];
	int iLargest, iExp = 1, iNum_Radix = 0, iPass_No,iI,iJ,iK,iR;

	iLargest = iArray[0];

	for(iI=1;iI<iArray_Size;iI++)
	{
		if(iArray[iI]>iLargest)
			iLargest = iArray[iI];
	}

	while(iLargest > 0)
	{
		iNum_Radix++;
		iLargest /= 10;
	}

	for(iPass_No=0;iPass_No < iNum_Radix; iPass_No++)
	{
		for(iK=0;iK<10;iK++)
		{
			iBuck_Count[iK] = 0;
			for(iI=0;iI<iArray_Size;iI++)
			{
				iR = (iArray[iI]/iExp) %10;
				iBucket[iR][iBuck_Count[iR]++] = iArray[iI];
			}
		}
		iI = 0;
		for(iK=0;iK<10;iK++)
		{
			for(iJ=0;iJ<iBuck_Count[iK];iJ++)
				iArray[iI++] = iBucket[iK][iJ];
		}
		iExp *= 10;
	}*/
	int iI, iTemp[MAX], iMax = 0, iExp = 1;
	for (iI = 0; iI < iArray_Size; iI++)
	{
		if (iArray[iI] > iMax)
		   iMax = iArray[iI];
	}
	while (iMax / iExp > 0)
	{
		int iNum_Radix[10] = {0};

		for (iI = 0; iI < iArray_Size; iI++)
		   iNum_Radix[iArray[iI] / iExp % 10]++;

		for (iI = 1; iI < 10; iI++)
		   iNum_Radix[iI] += iNum_Radix[iI - 1];

		for (iI = iArray_Size - 1; iI >= 0; iI--)
		   iTemp[--iNum_Radix[iArray[iI] / iExp % 10]] = iArray[iI];

		for (iI = 0; iI < iArray_Size; iI++)
			iArray[iI] = iTemp[iI];

		iExp *= 10;
		#ifdef SHOWPASS
		printf("\n\nPASS   : ");
		Prinnt_List();
		#endif
	}
}


///*
// * Function name	:	Get_Max
// *
// * Description		:	use this function to get the maximum number out of the given array.
// *
// * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
// *
// * Returns			:	Maximum number
// *
// */
//int Get_Max(int *iPtr)
//{
//	int iMax = *iPtr,iLocal;
//
//	for(iLocal=0;iLocal<iArray_Size;iLocal++)
//	{
//		if(*(iPtr+iLocal)>iMax)
//			iMax = *(iPtr+iLocal);
//	}
//	return iMax;
//}
//
//
///*
// * Function name	:	Do_Sort
// *
// * Description		:	use this function to get the array sort 1 time up on calling
// *
// * Parameters		:	int *iPtr ->  pointer to the array defined by user earlier
// * 						int iExp  ->  exponent that is 10^iExp
// *
// * Returns			:	Maximum number
// *
// */
//void Do_Sort(int *iPtr,int iExp)
//{
////	int iArray_Length = iArray_Size;
//	int iOutput[50];
//	int iLocal, iCount[10]={0};
//
//	for(iLocal=0;iLocal < iArray_Size;iLocal++)
//		iCount[((*iPtr+iLocal)/iExp)%10]++;
//
//	for(iLocal = 1; iLocal < 10 ; iLocal++)
//		iCount[iLocal] += iCount[iLocal-1];
//
//	for(iLocal = iArray_Size - 1; iLocal >= 0; iLocal--)
//	{
//		iOutput[iCount[((*iPtr+iLocal)/iExp)%10] -1 ] = *(iPtr+iLocal);
//		iCount[((*iPtr+iLocal)/iExp)%10]--;
//	}
//
//	for(iLocal = 0; iLocal < iArray_Size ; iLocal++)
//		*(iPtr+iLocal) = iOutput[iLocal];
//}


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

