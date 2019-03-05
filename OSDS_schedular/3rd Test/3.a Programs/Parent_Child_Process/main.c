/*
 * main.c
 *
 *  Created on: 23-Jul-2015
 *      Author: tejas
 */

#include 	<sys/types.h>
#include 	<sys/wait.h>
#include 	<unistd.h>
#include 	<stdio.h>
#include 	<stdlib.h>


int main()
{
	int iCount = 1;
	pid_t Pid;

	printf("The program has started now the child will count 1 to 10000.\n");

	printf("Now starting a child process wait for 2 Seconds\n");
	sleep(2);
	Pid = fork();																/*	Creating a child process*/
	switch(Pid)
	{
		case -1:

			printf("Creating a child process has failed\n");					/*	If child process is not created*/
			perror("Fork failed");
			exit(1);

		case 0:
			while(iCount++ < 10000)
			{
				printf("We are now in child process %d\n",iCount);				/*	If child process is created*/
				usleep(100);
			}
			break;

		default:

			wait(NULL);
			printf("\nThis is parent process\n");									/*	If child process has finished and returned to the
			 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	parent process*/
			printf("Child process has finished\n");
			printf("Parent process is going to terminet\n");
			exit(0);
			break;
	}
	return 0;
}
