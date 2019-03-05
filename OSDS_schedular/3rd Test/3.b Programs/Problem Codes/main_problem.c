/*
 * main.c
 *
 *  Created on: 24-Jul-2015
 *      Author: tejas
 */
/*Develop a parent-child process application, wherein child process calculates
 *square of numbers (using progressive arithmetic i.e. square of 2 = 2+2,
 *square of 3 = 3+3+3 and so on) from 1 to 1000 and parent process prints
 *result as soon as soon as child process produce it.
 *Use Pipes for IPC
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	<string.h>


int main()
{
	int iLocal = 1;																/*	Local variable that holds the value for making the square in
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	Child process*/
	int iFile_Pipes[2];															/*	File descriptor that are connected to processes in special way
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	that communication between the processes is done*/
	char chData[20];															/*	Data buffer for writting the square of a value to pipe*/
	char chBuffer[BUFSIZ+1];													/*	Buffer for reading back the written data in the child*/

	pid_t Child_Square;															/*	Child_Square is holding the result of function fork*/

	memset(chBuffer,0x00,sizeof(chBuffer));										/*	Clearing the buffer*/

	do
	{
		if(pipe(iFile_Pipes) == 0)												/*	Check the file descriptor for data to pass*/
		{
			Child_Square = fork();												/*	Creates a child process*/
			if(Child_Square == -1)
			{
				fprintf(stderr,"Child process creation failed!\n");				/*	Error message if the child creation fails*/
				exit(EXIT_FAILURE);												/*	And exit with status failure*/
			}
			if(Child_Square == 0)
			{
				long lSquare;													/*	Variable that holds the squared data*/
				int iCount;														/*	variable that holds the count for addition*/
				for(iCount = iLocal; iCount > 0; iCount--)
					lSquare += iLocal;											/*	Add the passed count to the lSquare variable till the
																					count becomes 0*/
				sprintf(chData,"%ld",lSquare);									/*	Prints the squared data into the string*/
				write(iFile_Pipes[1], chData, strlen(chData));					/*	Writes to the file descriptors so that parent can read it*/
				usleep(100);													/*	For better visibility only*/
				exit(EXIT_SUCCESS);												/*	Exit from the child process so that parent can run*/
			}
			else
			{
				read(iFile_Pipes[0],chBuffer,BUFSIZ);							/*	Read the data which was earlier written by child*/
				printf("Square of %d is: %s\n",iLocal, chBuffer);				/*	Prints the squared data to the Console*/
				usleep(100);													/*	For sync with the childs 100 uSec delay*/
			}
		}
	}
	while(iLocal++ < 1000);														/*	Looping it upto 1000 times for getting the square of int
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	from 1 to 1000*/
	printf("Termainating after 2 seconds...\n");
	sleep(2);
	printf("Terminated..");
	exit(EXIT_SUCCESS);
}
