/*
 * main.c
 *
 *  Created on: 30-Jul-2015
 *      Author: tejas
 */

/* Develop a two-threaded application, wherein each thread writes numbers from
 * (1 to 1000) in a same file. Thread one should prefix “#” and thread 2 should
 * prefix “$” before writing numbers. Make sure at a time only one thread can
 * write to a file. Also design this application in such a way that both threads
 * run in parallel.
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<semaphore.h>
#include	<pthread.h>


FILE 			*fptrData;														/*	File pointer to open a file for writing*/
pthread_t 		Result_Threads[2];												/*	Threads*/
void 			*vptrThread_Result[2];											/*	Thread joining is handled by this variable*/
pthread_mutex_t Lock_The_Access = PTHREAD_MUTEX_INITIALIZER;					/*	Mutex for locking access between two threads*/
pthread_cond_t  Condition_Var   = PTHREAD_COND_INITIALIZER;						/*	Condition variable between threads to communicate*/
int				iCounter = 1;


void 		*Input_Dollar(void *);												/*	Thread function for writing data in file with dollar*/
void 		*Input_Hash(void *);												/*	Thread function for writting data in file with hash*/
void 		Join_Thread(void);													/*	Joins multiple threads*/



int main()
{
	int iResult[2];																/*	Results of creating threads is stored in it*/
	fptrData = fopen("Data_Output","w");										/*	Opening a file for writing data*/

	iResult[0] = pthread_create(&Result_Threads[0],								/*	Creating a thread*/
								NULL,Input_Dollar,NULL);
	if (iResult[0] != 0)														/*	Error handling is done in here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	iResult[1] = pthread_create(&Result_Threads[1],								/*	Creating another thread*/
								NULL,Input_Hash,NULL);
	if (iResult[1] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	Join_Thread();																/*	Joins threads*/

	int iDest = pthread_cond_destroy(&Condition_Var);							/*	Destroy the condition variable after its usage*/
	if (iDest == 1)
	{
		perror("Error Destroying the condition variable\n");					/*	Error if Condition variable is still being used but that
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	are rare case posibilities*/
	}

	iDest = pthread_mutex_destroy(&Lock_The_Access);
	if(iDest == 1)
	{
		perror("Error Destroying the Mutex\n");									/*	Error if Mutex can not be deleted*/
	}

	if(fclose(fptrData)==EOF)													/*	Close the file after the usage*/
	{
		perror("Error in closing the file\n");
	}
	return 0;
}


/*
 * Function name	:	Input_Dollar
 *
 * Description		:	This function is used by the thread for writing the number with
 * 						dollar sign as prefix
 *
 * Parameters		:	void *vptrA -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */

void *Input_Dollar(void *vptrA)
{
	while(iCounter <= 1000)
	{
		pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
		pthread_cond_wait(&Condition_Var, &Lock_The_Access);					/*	Wait till the Condition variable is signled*/
		fprintf(fptrData,"\t$%d\n",iCounter);									/*	Print the data*/
		iCounter++;																/*	Increment the counter*/
		pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/
	}
	pthread_exit(0);															/*	Exit the thread after the execution is done*/
}


/*
 * Function name	:	Input_Hash
 *
 * Description		:	This function is used by the thread for writing the number with
 * 						hash sign as prefix
 *
 * Parameters		:	void *vptrA -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */
void *Input_Hash(void *vptrA)
{
	while(iCounter <= 1000)
	{
		pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
		fprintf(fptrData,"#%d",iCounter);										/*	Print the data*/
		pthread_cond_signal(&Condition_Var);									/*	Signal the condition variable*/
		pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/
		usleep(1000);															/*	for better viewing of output*/
	}
	pthread_exit(0);															/*	Exit the thread after the execution is done*/
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
	int iResult[2],iLocal;
	printf("\n");
	for(iLocal = 0; iLocal < 2; iLocal++)
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
