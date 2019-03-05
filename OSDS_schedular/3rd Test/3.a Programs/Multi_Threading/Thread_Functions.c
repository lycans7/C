/*
 * Thread_Functions.c
 *
 *  Created on: 24-Jul-2015
 *      Author: tejas
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "Thread_Header.h"



int 			iC[3][3];									/*This matrix holds the resultant matrix*/

pthread_t 		Result_Threads[9];
void 			*vptrThread_Result[9];
extern Matrix_t Argument_Matrix;


/*
 * Function name	:	Get_Two_Matrix
 *
 * Description		:	use this function to get two matrix for multiplication from user
 *
 * Parameters		:	None
 *
 * Returns			:	Object of the matrix in which user has enterd two matrix data
 */
Matrix_t Get_Two_Matrix(void)
{
	Matrix_t iMatrix;
	int iLocal;
	for(iLocal = 0; iLocal < 2; iLocal++)
	{
		printf("Enter %d 3X3 Matrix\n",iLocal+1);
		iMatrix = Get_Matrix(iMatrix,iLocal);

		printf("Your given matrix is\n");
		Print_Matrix(iMatrix,iLocal);
	}
	return iMatrix;
}


/*
 * Function name	:	Print_Matrix
 *
 * Description		:	use this function to print particular matrix which was earlier given
 * 						by user
 *
 * Parameters		:	Matrix_t iMatrix -> object of the matrix in which data has been stroed
 * 						int iLocal -> this suggest the function which matrix to print if 0
 * 									  it prints the first matrix given by user if 0 it prints
 * 									  the second matrix given by user.
 *
 * Returns			:	None
 */
void Print_Matrix(Matrix_t iMatrix, int iLocal)
{
	int iLocal1,iLocal2;
	for(iLocal1 = 0 ; iLocal1 < 3; iLocal1++)
	{
			for(iLocal2 = 0 ; iLocal2 < 3; iLocal2++)
			{
				if(iLocal == 0)
					printf("%d\t",iMatrix.iA[iLocal1][iLocal2]);// + (iLocal1 * iSize) + iLocal2);
				else
					printf("%d\t",iMatrix.iB[iLocal1][iLocal2]);
			}
			printf("\n");
	}
	printf("\n");
}


/*
 * Function name	:	Get_Matrix
 *
 * Description		:	use this function to print particular matrix which was earlier given
 * 						by user
 *
 * Parameters		:	Matrix_t iMatrix -> object of the matrix in which data has to be stroed
 * 						int iLocal -> this suggest the function that in which matrix to store
 * 									  the data if 0 it prints the first matrix given by user
 * 									  if 1 it prints the second matrix given by user.
 *
 * Returns			:	Object of the structure matrix in which data has been stored
 */

Matrix_t Get_Matrix(Matrix_t iMatrix,int iLocal)
{
	int iLocal1,iLocal2;
		for(iLocal1 = 0 ; iLocal1 < 3; iLocal1++)
		{
				for(iLocal2 = 0 ; iLocal2 < 3; iLocal2++)
				{
					if(iLocal == 0)
						scanf("%d",&(iMatrix.iA[iLocal1][iLocal2]));// + (iLocal1 * iSize) + iLocal2));
					else
						scanf("%d",&(iMatrix.iB[iLocal1][iLocal2]));
				}
		}
	printf("\n");
	return iMatrix;
}


/*
 * Function name	:	Print_Result_Matrix
 *
 * Description		:	use this function to print resultant matrix by the multiplication of
 * 						two user given matrix
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */

void Print_Result_Matrix(void)
{
	int iLocal,iLocal1;
	printf("\nMultiplication of your given 2 matrix is\n");
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		for(iLocal1 = 0; iLocal1 < 3; iLocal1++)
			printf("%d\t",iC[iLocal][iLocal1]);
		printf("\n");
	}
	printf("\n");
}


/*
 * Function name	:	Create_Thread
 *
 * Description		:	use this function to create as many threads as matrix supports
 *
 * Parameters		:	int iLocal -> number of function to be used with thread is suggetsted by this int
 *
 * Returns			:	None
 */

void Create_Thread(int iLocal)
{
	int iResult[9];
	switch(iLocal)
	{
		case 0:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C11,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 1:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C12,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 2:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C13,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 3:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C21,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 4:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C22,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 5:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C23,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 6:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C31,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 7:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C32,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		case 8:
			iResult[iLocal] = pthread_create(&Result_Threads[iLocal],NULL,Matrix_Multiplication_C33,(void *)&Argument_Matrix);
			if (iResult[iLocal] != 0)
			{
				printf("Thread creation failed\n");
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			break;

		default:
			printf("No more functions to perform\n");
			break;
	}
}


/*
 * Function name	:	Join_Thread
 *
 * Description		:	use this function to join all the created threads.
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */

void Join_Thread(void)
{
	int iResult[9],iLocal;
	printf("\n");
	for(iLocal = 0; iLocal < 9; iLocal++)
	{
		printf("Joining Thread %d\n",iLocal+1);
		iResult[iLocal] = pthread_join(Result_Threads[iLocal],&vptrThread_Result[iLocal]);
		if(iResult[iLocal] != 0)
		{
			printf("Thread joining has failed!\n");
			perror("Thread joining has failed!");
			exit(EXIT_FAILURE);
		}
	}
}


/*
 * Function name	:	Matrix_Multiplication_C11
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C11(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 0,iMul_Coll = 0;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[0][0] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C12
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C12(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 0,iMul_Coll = 1;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[0][1] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C13
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C13(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 0,iMul_Coll = 2;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[0][2] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C21
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C21(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 1,iMul_Coll = 0;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[1][0] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C22
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C22(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 1,iMul_Coll = 1;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[1][1] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C23
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C23(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 1,iMul_Coll = 3;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[1][2] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C31
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C31(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 2,iMul_Coll = 0;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[2][0] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C32
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C32(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 2,iMul_Coll = 1;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[2][1] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);

		/*(*(int *)iMatrix->iA+iLocal+iMul_Row) * (*(int *)iMatrix->iB+iLocal+iMul_Coll);
		iMul_Row += 3;
		iMul_Coll += 3;*/
	}
	pthread_exit(0);
}



/*
 * Function name	:	Matrix_Multiplication_C33
 *
 * Description		:	This function is used by the thread for computing given task
 *
 * Parameters		:	void *vptrA -> This is pointer holds an argument that has been
 * 									   passed in function while creating thread.
 *
 * Returns			:	None
 */

void *Matrix_Multiplication_C33(void *vptrA)
{
	Matrix_p iMatrix;

	iMatrix = (Matrix_p)vptrA;

	int iLocal,iMul_Row = 2,iMul_Coll = 2;
	for(iLocal = 0; iLocal < 3; iLocal++)
	{
		iC[2][2] += (iMatrix->iA[iMul_Row][iLocal]) * (iMatrix->iB[iLocal][iMul_Coll]);//+iLocal+iMul_Coll);
	}
	pthread_exit(0);
}
