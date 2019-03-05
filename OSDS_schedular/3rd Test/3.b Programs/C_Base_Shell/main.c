/*
 * main.c
 *
 *  Created on: 29-Jul-2015
 *      Author: tejas
 */

/*
 * Develop a simple C based shell, which continuously scans for user input
 * and accordingly execute commands. This shell should validate user inputs.
 * Extra: How would you extend this shell so it provides “|” (Linux pipe)
 * feature.
 *
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<sys/wait.h>
#include	<sys/types.h>
#include	<fcntl.h>


#define		MAX_ARGS		64													/*	Linux supports maximum of 64 arguments in a command*/



int main()
{
	char 	chLine[1024];														/*	Line scanned from stdin is stored in this string*/
	char 	*chptrArgs[MAX_ARGS];												/*	This two dimensional pointer points to the options
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	if any in the string as well as the command passed in
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	in the string*/
	char 	**chptrNext = chptrArgs;											/*	This is the double pointer same as above but it points
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	directly to the arguments in the string taken from the stdin*/
	char 	*chptrTemp = NULL;													/*	Temp pointer points to the current argument in the string*/

	int		iBackground;														/*	If a command has & in it this variable indicate the parent
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	process to continue execution like in shell*/
	int		iStatus;															/*	This variable holds the return status of the child process*/

	pid_t 	Child_Porcess;														/*	This variable holds the PID of parent process*/

	printf("This is C base shell some command will not work\n");
	printf("$: ");
	sleep(2);
	while(1)
	{
		memset(chLine,0x00,sizeof(chLine));										/*	Cleaning the line before takin input from user so that
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	two commands do not get confused by this shell*/
		fgets(chLine,sizeof(chLine),stdin);										/*	Scans the line till the new line "\n" is read*/


		chptrNext = chptrArgs;													/*	Points to the arguments holding array of pointer
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	this helps get back to the first argument after
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	executing the first command.*/
		iBackground = 0;														/*	Default init of background process*/

		chptrTemp = strtok(chLine, " ");										/*	Process the string for getting the commands*/
		while (chptrTemp != NULL)
		{
			*chptrNext++ = chptrTemp;											/*	Copies the pointer to the array of pointer*/
			chptrTemp = strtok(NULL, " ");										/*	Check for the NULL pointer in the string*/
		}
		if(*(chptrNext - 1) != NULL)
		{
			strtok(*(chptrNext -1),"\n");
			if(strcmp(*(chptrNext-1),"exit")==0)								/*	If we have "exit" command in the read string terminate the program*/
			{
				printf("About to exit the shell!!!\n");
				break;
			}

			else if(strcmp(*(chptrNext-1),"&") == 0)							/*	If "&" is found in the string set the variable*/
			{
				iBackground = 1;
				*(chptrNext-1) = NULL;
			}
		}
		*chptrNext = NULL;														/*	End of the command is pointed by the NULL*/


		Child_Porcess = fork();													/*	Create the child process*/
		if(Child_Porcess == -1)
		{
			fprintf(stderr,"Child process creation error\n");
			exit(EXIT_FAILURE);
		}
		/**************************** Child Porcess ***************************/
		if(Child_Porcess == 0)
		{
			if(execvp(chptrArgs[0], chptrArgs) == -1)							/*	Execute the command scanned from the stdin*/
			{
				fprintf(stderr,"Error Executing the Command\n");				/*	If error print the message*/
				exit(EXIT_FAILURE);
			}
		}
		/************************** Parent Porcess ****************************/
		else
		{
			pid_t Check_Process;												/*	Variable that stores the status of the executed commands*/
			int iBreak = 0;														/*	This variable is set to 1 if process has returned after execution*/
			if(iBackground == 0)
			{
				while(1)
				{
					while((Check_Process = waitpid(-1, &iStatus, WNOHANG)) > 0)	/*	Wait till the child process end*/
					{
						iBreak = 1;
					}
					if(iBreak)
						break;
				}
			}
			printf("$: ");
		}
	}
	sleep(1);
	printf("\n\nAnswer of the extra question\n");								/*	Indication of answer of the extra question*/
	printf("Extra:\tHow would you extend this shell so it provides "			/*	Extra question*/
			"\"|\" (Linux pipe) feature?\n"
			"Ans:"																/*	Answer of the extra question*/
			"\tTo extend this shell to provide | feature we should use "
			"\n\tthe files so that we can redirect\n"
			"\tthe inputs or outputs of the commands to the file and "
			"\n\twhen executing the next command after |\n"
			"\tthe files in which the data are stored can be "
			"\n\tread again and print on the screen\n");

	exit(EXIT_SUCCESS);
}
