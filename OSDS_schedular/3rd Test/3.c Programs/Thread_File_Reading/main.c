/*
 * main.c
 *
 *  Created on: 31-Jul-2015
 *      Author: tejas
 */


/*
 * Develop a multi threaded producer consumer application.
 * • Three thread application, wherein each thread invokes at fixed
 * (for 1st thread 10sec, 2nd thread 20sec and 3rd thread 30sec)
 * • When thread will invoke, it should read next chunk of 1KB from the
 * target file. After reading chunk apply unique encryption scheme
 * (e.g. add 0x50 on every bytes of 1kb chunk).Each thread having
 * unique encryption scheme. After encryption, dumps encrypted chunk
 * to another file.
 * • At a time simultaneously only two threads can read from a target
 * file. If at a time two threads are ready to read then both threads
 * should be able to read data from target file.
 *
 */



#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<semaphore.h>
#include	<pthread.h>


FILE			*fptrRead_File;
FILE			*fptrThread1_Out;
FILE			*fptrThread2_Out;
FILE			*fptrThread3_Out;

pthread_t 		Result_Threads[3];												/*	Threads*/
void 			*vptrThread_Result[3];											/*	Thread joining is handled by this variable*/

int				iRead_Access = 2;

pthread_mutex_t Lock_The_Access = PTHREAD_MUTEX_INITIALIZER;					/*	Mutex for locking access between two threads*/
pthread_cond_t  Condition_Var   = PTHREAD_COND_INITIALIZER;						/*	Condition variable between threads to communicate*/



void 			*Thread1_Read_Write(void *);									/*	Thread function for encryption 1*/
void 			*Thread2_Read_Write(void *);									/*	Thread function for encryption 2*/
void 			*Thread3_Read_Write(void *);									/*	Thread function for encryption 3*/



int main()
{
	int iResult[3];																/*	Results of creating threads is stored in it*/
	fptrRead_File = fopen("Data_Output","r");									/*	Opening a file for writing data*/
	if(fptrRead_File == NULL)
		perror("Error opening a file\n");


	/******************Creating Threads****************************************/
	iResult[0] = pthread_create(&Result_Threads[0],								/*	Creating a thread*/
								NULL,Thread1_Read_Write,NULL);
	if (iResult[0] != 0)														/*	Error handling is done in here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	iResult[1] = pthread_create(&Result_Threads[1],								/*	Creating another thread*/
								NULL,Thread2_Read_Write,NULL);
	if (iResult[1] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}
	
	iResult[2] = pthread_create(&Result_Threads[2],								/*	Creating another thread*/
								NULL,Thread3_Read_Write,NULL);
	if (iResult[2] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	/*********************Joining Threads**************************************/
	iResult[0] = pthread_join(Result_Threads[0],&vptrThread_Result[0]);			/*	Wait for the thread 1 to join*/
	printf("Joining Thread %d\n",0+1);
	if(iResult[0] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	iResult[1] = pthread_join(Result_Threads[1],&vptrThread_Result[1]);			/*	Wait for the thread 2 to join*/
	printf("Joining Thread %d\n",1+1);
	if(iResult[1] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	iResult[2] = pthread_join(Result_Threads[2],&vptrThread_Result[2]);			/*	Wait for the thread 3 to join*/
	printf("Joining Thread %d\n",2+1);
	if(iResult[2] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	/**********************Closing the file************************************/
	if(fclose(fptrRead_File) == EOF)											/*	Closing the file after the purpose fulfilled*/
		perror("Error closing the file opened for reading\n");

	/****************Destroying the Mutex variable****************************/
	int iDest = pthread_mutex_destroy(&Lock_The_Access);
	if(iDest == 1)
	{
		perror("Error Destroying the Mutex\n");									/*	Error if Mutex can not be deleted*/
	}


	printf("Terminating the main\n");
	return 0;
}



/*
 * Function name	:	Thread1_Read_Write
 *
 * Description		:	This function is used by the thread for reading predefined
 * 						bytes from the file opened in main and write to a different
 * 						file with encryption such as adding 0x50 on every byte
 *
 * Parameters		:	void *vptrDummy -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */

void *Thread1_Read_Write(void *vptrDummy)
{
	size_t 	Read_Count;
	size_t 	Write_Count;
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int		iBreak = 0;

	char	chBuffer[1200];

	fptrThread1_Out = fopen("Thread1_Data.txt","w");
	if(fptrThread1_Out == NULL)
			perror("Error opening a file in thread 1\n");

	while(1)
	{
		sleep(10);

		fseek(fptrRead_File,iCount*1024,SEEK_SET);

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);

			if(Read_Count < 1024)
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x50;
			}

			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread1_Out);
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 1\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}

		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

		if(iBreak == 1)
			break;
	}

	fprintf(fptrThread1_Out,"\nEOF\n");

	if(fclose(fptrThread1_Out) == EOF)
	{
		perror("Error closing the file opened for writing data in thread 1\n");
	}

	printf("Terminating Thread1\n");
	pthread_exit(0);
}



/*
 * Function name	:	Thread2_Read_Write
 *
 * Description		:	This function is used by the thread for reading predefined
 * 						bytes from the file opened in main and write to a different
 * 						file with encryption such as adding 0x60 on every byte
 *
 * Parameters		:	void *vptrDummy -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */
void *Thread2_Read_Write(void *vptrDummy)
{
	size_t 	Read_Count;
	size_t 	Write_Count;
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int		iBreak = 0;

	char	chBuffer[1200];

	fptrThread2_Out = fopen("Thread2_Data.txt","w");
	if(fptrThread2_Out == NULL)
		perror("Error opening a file in thread 2\n");


	while(iBreak == 0)
	{
		sleep(20);

		fseek(fptrRead_File,iCount*1024,SEEK_SET);

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);

			if(Read_Count < 1024)
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x60;
			}
			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread2_Out);
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 2\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}

		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

	}

	fprintf(fptrThread2_Out,"\nEOF\n");

	fclose(fptrThread2_Out);

	printf("Terminating Thread2\n");
	pthread_exit(0);
}



/*
 * Function name	:	Thread3_Read_Write
 *
 * Description		:	This function is used by the thread for reading predefined
 * 						bytes from the file opened in main and write to a different
 * 						file with encryption such as adding 0x70 on every byte
 *
 * Parameters		:	void *vptrDummy -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */
void *Thread3_Read_Write(void *vptrDummy)
{
	size_t 	Read_Count;
	size_t 	Write_Count;
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int 	iBreak = 0;

	char	chBuffer[1200];

	fptrThread3_Out = fopen("Thread3_Data.txt","w");
	if(fptrThread3_Out == NULL)
		perror("Error opening a file in thread 3\n");

	while(1)
	{
		sleep(30);

		fseek(fptrRead_File,iCount*1024,SEEK_SET);

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);

			if(Read_Count < 1024)
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x70;
			}
			pthread_mutex_lock(&Lock_The_Access);									/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);									/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread3_Out);
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 3\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}

		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

		if(iBreak == 1)
			break;
	}

	fprintf(fptrThread3_Out,"\nEOF\n");

	if(fclose(fptrThread3_Out) == EOF)
	{
		perror("Error closing the file opened for writing data in thread 3\n");
	}

	printf("Terminating Thread3\n");
	pthread_exit(0);
}

