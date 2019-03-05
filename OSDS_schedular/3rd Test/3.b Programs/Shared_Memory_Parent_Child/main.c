/*
 * main.c
 *
 *  Created on: 27-Jul-2015
 *      Author: tejas
 */


/* Develop a parent-child process application, wherein child process
 * at random duration calculates square of numbers (via above method)
 * from 1 to 1000 and parent process prints result as soon as soon
 * as child process produce it. Use Shared-memory for IPC
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	<sys/shm.h>
#include 	<sys/types.h>
#include 	<sys/wait.h>


#define		MAX_SQR		1000														/*	maximum number upto which sqaure is to be found*/


typedef struct Shared_Mem															/*	Shared memory data structure*/
{
	int iWritten;
	char chBuffer[BUFSIZ];
}Pipe_t, *Pipe_p;



int main()
{
	int iRunning = 1;																/*	Variable set so that applcation can run till it is set*/
	char chBuffer[BUFSIZ];															/*	Buffer for transferring calculated data to store*/
	int iLocal;																		/*	Local variable which holds the value for which the square
																						to be done*/

	int iShared_Mem_Id;																/*	Shared memory id holding variable*/
	Pipe_p Shared_Data;																/*	Pointer object of above defined structure*/
	pid_t Child_Process;															/*	Variable that holds the value of the child process
																						/ perent process*/
	void *vptrShared_Memory = (void *)0;											/*	Pointer that points to the shared memory later in
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	the program*/


	Child_Process = fork();															/*	Creates a child process*/
	if(Child_Process == -1)
	{
		fprintf(stderr,"Child process creation failed!\n");							/*	Error message if the child creation fails*/
		exit(EXIT_FAILURE);															/*	And exit with status failure*/
	}
	/*************************Child Process***********************************/
	if(Child_Process == 0)
	{
		long lSquare;																/*	Variable that holds the squared data*/
		int iCount;																	/*	variable that holds the count for addition*/

		/********************Get the Shared memory****************************/
		iShared_Mem_Id = shmget((key_t)1234, sizeof(Pipe_t), 0666 | IPC_CREAT);		/*	Get the shared memory id after creating it*/
		if (iShared_Mem_Id == -1)
		{
			fprintf(stderr, "Failed in getting shared memory in "					/*	Error message if it fails*/
					"\"Child Process\"\n");
			exit(EXIT_FAILURE);
		}

		/*****************Attach the Shared memory****************************/
		vptrShared_Memory = shmat(iShared_Mem_Id, (void *)0, 0);					/*	Attach to the shared memory gained earlier by shmget()*/
		if (vptrShared_Memory == (void *)-1)
		{
			fprintf(stderr, "Shared memory attachment to the process failed "		/*	Error message if it fails*/
					"in \"Child Process\"\n");
			exit(EXIT_FAILURE);
		}
		printf("Shared memoey attached to "											/*	Prints the address of the shared memory*/
				"the Child Process is %p\n",vptrShared_Memory);


		Shared_Data = (Pipe_p) vptrShared_Memory;									/*	Above defined structure object points to the sahred memory*/


		while(iRunning)
		{
			while(iLocal++ < MAX_SQR)
			{
				while(Shared_Data->iWritten == 1)
				{
					usleep(15000);													/*	Sleeps for 15mSec*/
					printf("Waiting for Parent Process to print the data\n");
				}

				for(iCount = iLocal; iCount > 0; iCount--)
					lSquare += iLocal;
				sprintf(chBuffer,"%ld",lSquare);									/*	Prints the squared data into the string*/

				strcpy(Shared_Data->chBuffer,chBuffer);								/*	Copy the calculated data to the Shared memory*/

				memset(chBuffer,0x00,sizeof(chBuffer));								/*	Clear the holding buffer for next calculation*/
				lSquare = 0;														/*	Making the value to 0 so does not end up in the
				 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	wrong calculation*/
				Shared_Data->iWritten = 1;
				usleep(500);
			}
			break;
		}
		iRunning = 0;
		printf("Dettaching the shared memory from Child process\n");

		/***************Dettach the Shared memory*****************************/
		if (shmdt(vptrShared_Memory) == -1)											/*	Dettach the attched shared memory*/
		{
			fprintf(stderr, "Shared memory detattachment failed\n");				/*	Error message if it fails*/
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	/************************Parent Process***********************************/
	else
	{
		/********************Get the Shared memory****************************/
		iShared_Mem_Id = shmget((key_t)1234, sizeof(Pipe_t), 0666 | IPC_CREAT);		/*	This is similar to above defined function gets the
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	shared memory*/
		if (iShared_Mem_Id == -1)
		{
			fprintf(stderr, "Failed in getting shared memory in "					/*	Error message if it fails*/
					"\"Parent Process\"\n");
			exit(EXIT_FAILURE);
		}

		/*****************Attach the Shared memory****************************/
		vptrShared_Memory = shmat(iShared_Mem_Id, (void *)0, 0);					/*	Attach the sahred memory*/
		if (vptrShared_Memory == (void *)-1)
		{
			fprintf(stderr, "Shared memory attachment to the process "				/*	Error message if it fails*/
					"failed in \"Parent Process\"\n");
			exit(EXIT_FAILURE);
		}
		printf("Shared memoey attached to the "										/*	Prints the shared memory address*/
				"Parent process is %p\n",vptrShared_Memory);


		Shared_Data = (Pipe_p) vptrShared_Memory;									/*	Same as the child process*/

		while(iRunning)
		{
			while(Shared_Data->iWritten)
			{
				printf("Square of the %d is: %s\n",iLocal+1,Shared_Data->chBuffer);	/*	Prints the sqaure of a number produced by the Child process*/
				Shared_Data->iWritten = 0;											/*	Data has been read indication*/
				iLocal++;															/*	Incrementing the local variable*/
				if(iLocal >= MAX_SQR)												/*	If local variable reaches the maximum value break the loop*/
				{
					iRunning = 0;
					break;
				}
			}
		}
		printf("Parent is ending\n");
		printf("Dettaching the shared memory from the program and "
									"removing it from the system\n");
		/***************Dettach the Shared memory*****************************/
		if (shmdt(vptrShared_Memory) == -1)											/*	Dettach the shared memory*/
		{
			fprintf(stderr, "Shared memory detattachment failed\n");				/*	Error if it fails*/
			exit(EXIT_FAILURE);
		}
		/***************Delete the Shared memory******************************/
		if (shmctl(iShared_Mem_Id, IPC_RMID, 0) == -1)								/*	Delete the shared memory area*/
		{
			fprintf(stderr, "Shared memory removal(IPC_RMID) failed\n");			/*	Error if it fails*/
			exit(EXIT_FAILURE);
		}
	}
	printf("Terminating after 2 Secs\n");
	sleep(2);
	printf("Terminated.....\n");
	exit(EXIT_SUCCESS);
}
