/*
 * main.c
 *
 *  Created on: 23-Jul-2015
 *      Author: tejas
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "Thread_Header.h"

Matrix_t Argument_Matrix;

int main()
{
	int iLocal;

	Argument_Matrix = Get_Two_Matrix();

	printf("Your given 2 matrix are as:\n");
	Print_Matrix(Argument_Matrix,0);
	Print_Matrix(Argument_Matrix,1);

	for(iLocal = 0; iLocal < 9; iLocal++)
	{
		printf("Creating Thread %d for (%d)th indices\n",iLocal+1,iLocal);
		Create_Thread(iLocal);
	}
	Join_Thread();

	Print_Result_Matrix();

	printf("Terminating...\n");
	return 0;
}
