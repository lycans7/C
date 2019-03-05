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
 * Extend above application for status display purpose
 * • After an iteration of execution thread should notify operation
 * 	 statistics to book-keeping thread.
 * • Statistics for each thread are: % read completion, iteration
 *   count, number of words read
 * • When user generates signal (Ctrl+C or SIGINT), application
 *   should terminate gracefully.
 * • Hint: Use Condition Variables to notify book-keeping thread,
 *   is there any other mechanism to notify book-keeping thread?
 *   Which is better and why?
 */



#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<semaphore.h>
#include	<pthread.h>
#include	<signal.h>




typedef struct Data_Passing
{
	int 		iPercent_Read;													/*	Percentage file read*/
	int			iCount_Read;													/*	How many times the file is read*/
	int			iNum_Words;														/*	Number of words read*/
	int			iBreak;															/*	Breaks the while loop when Ctrl+C is pressed*/
}Thread_Details_t;

Thread_Details_t Thread1, Thread2, Thread3;


FILE			*fptrRead_File;
FILE			*fptrThread1_Out;
FILE			*fptrThread2_Out;
FILE			*fptrThread3_Out;

pthread_t 		Result_Threads[4];												/*	Threads*/
void 			*vptrThread_Result[4];											/*	Thread joining is handled by this variable*/

int				iRead_Access = 2;												/*	Simultaneous execution of the Threads is done through this variable*/
long			lFile_Size;														/*	To get the file size in bytes*/


pthread_mutex_t Lock_The_Access = PTHREAD_MUTEX_INITIALIZER;					/*	Mutex for locking access between two threads*/


pthread_cond_t  Thread1_Details = PTHREAD_COND_INITIALIZER;						/*	Thread1 Details to be obtained to print in book keeping*/
pthread_cond_t  Thread2_Details = PTHREAD_COND_INITIALIZER;						/*	Thread2 Details to be obtained to print in book keeping*/
pthread_cond_t  Thread3_Details = PTHREAD_COND_INITIALIZER;						/*	Thread3 Details to be obtained to print in book keeping*/


void			Interrupt_Occured(int);											/*	Traps the interrupt*/

void 			*Thread1_Read_Write(void *);									/*	Thread function for encryption 1*/
void 			*Thread2_Read_Write(void *);									/*	Thread function for encryption 2*/
void 			*Thread3_Read_Write(void *);									/*	Thread function for encryption 3*/
void 			*Book_Keeping_Thread(void *);									/*	Thread function for Book keeping purpose*/



int main()
{
	int iResult[4];																/*	Results of creating threads is stored in it*/

	(void) signal(SIGINT,Interrupt_Occured);									/*	Signal function scans for the Ctrl+C*/

	fptrRead_File = fopen("Data_Output","r");									/*	Opening a file for writing data*/

	/******************Open a file for reading*********************************/
	fseek(fptrRead_File,0L,SEEK_END);
	lFile_Size = ftell(fptrRead_File);
	fseek(fptrRead_File,0L,SEEK_SET);

	fprintf(stderr,"File size is %ldKB\n",(lFile_Size/1024));

	if(fptrRead_File == NULL)
		perror("Error opening a file\n");


	/*****************Creating a thread for book keeping***********************/
	iResult[0] = pthread_create(&Result_Threads[0],								/*	Creating Book keeping thread*/
								NULL,Book_Keeping_Thread,NULL);
	if (iResult[0] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	/*****************Creating a thread for thread1 function*******************/
	iResult[1] = pthread_create(&Result_Threads[1],								/*	Creating a thread*/
								NULL,Thread1_Read_Write,NULL);
	if (iResult[1] != 0)														/*	Error handling is done in here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	/*****************Creating a thread for thread2 function*******************/
	iResult[2] = pthread_create(&Result_Threads[2],								/*	Creating another thread*/
								NULL,Thread2_Read_Write,NULL);
	if (iResult[2] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	/*****************Creating a thread for thread3 function*******************/
	iResult[3] = pthread_create(&Result_Threads[3],								/*	Creating another thread*/
								NULL,Thread3_Read_Write,NULL);
	if (iResult[3] != 0)														/*	Error handling is done here*/
	{
		printf("Thread1 creation failed\n");
		perror("Thread1 creation failed\n");
		exit(EXIT_FAILURE);
	}


	/*****************Joining thread1******************************************/
	iResult[0] = pthread_join(Result_Threads[0],&vptrThread_Result[0]);			/*	Wait for the thread 1 to join*/
	printf("Joining Thread %d\n",0+1);
	if(iResult[0] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	/*****************Joining thread2******************************************/
	iResult[1] = pthread_join(Result_Threads[1],&vptrThread_Result[1]);			/*	Wait for the thread 2 to join*/
	printf("Joining Thread %d\n",1+1);
	if(iResult[1] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	/*****************Joining thread3******************************************/
	iResult[2] = pthread_join(Result_Threads[2],&vptrThread_Result[2]);			/*	Wait for the thread 3 to join*/
	printf("Joining Thread %d\n",2+1);
	if(iResult[2] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	/*****************Joining thread4******************************************/
	iResult[3] = pthread_join(Result_Threads[3],&vptrThread_Result[3]);			/*	Wait for the Book keeping to join*/
	printf("Joining Thread %d\n",3+1);
	if(iResult[3] != 0)
	{
		printf("Thread joining has failed!\n");									/*	Error message*/
		perror("Thread joining has failed!");
		exit(EXIT_FAILURE);
	}

	/****************Closing the opened file***********************************/
	if(fclose(fptrRead_File) == EOF)											/*	Closing the file after the purpose fulfilled*/
		perror("Error closing the file opened for reading\n");

	/****************Destroying the condition variables************************/
	int iDest = pthread_cond_destroy(&Thread1_Details);							/*	Destroy the condition variable after its usage*/
	if (iDest == 1)
	{
		perror("Error Destroying the condition variable\n");					/*	Error if Condition variable is still being used but that
																					are rare case posibilities*/
	}

	/****************Destroying the condition variables************************/
	iDest = pthread_cond_destroy(&Thread2_Details);								/*	Destroy the condition variable after its usage*/
	if (iDest == 1)
	{
		perror("Error Destroying the condition variable\n");					/*	Error if Condition variable is still being used but that
																					are rare case posibilities*/
	}

	/****************Destroying the condition variables************************/
	iDest = pthread_cond_destroy(&Thread3_Details);								/*	Destroy the condition variable after its usage*/
	if (iDest == 1)
	{
		perror("Error Destroying the condition variable\n");					/*	Error if Condition variable is still being used but that
																					are rare case posibilities*/
	}

	/****************Destroying the Mutex variable****************************/
	iDest = pthread_mutex_destroy(&Lock_The_Access);
	if(iDest == 1)
	{
		perror("Error Destroying the Mutex\n");									/*	Error if Mutex can not be deleted*/
	}

	printf("Terminating the main\n");

	printf("\nIs there any other mechanism to notify book-keeping thread?\n"
			"Which is better and why?\n");
	printf("ANS:\tPipes, Message Queue and Shared Memory may be used to notify as,\n"
			"\tas read the data. In all of the above mentioned mechanism the better one\n"
			"\tis Message Queue through which message can be passed to\n"
			"\tbook-keeping Thread. In all cases the use of Message Queue\n"
			"\tis better as locking and waiting on is not required.\n"
			"\tData can be directly read by the thread and processed by the same\n");


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
	size_t 	Read_Count;															/*	Count of bytes that has been read from the file*/
	size_t 	Write_Count;														/*	Count of bytes that is about to written in the file*/
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int		iBreak = 0;															/*	Break variable indicates the end of the reading*/

	char	chBuffer[1200];

	fptrThread1_Out = fopen("Thread1_Data.txt","w");							/*	Open a file for writing encrypted data*/
	if(fptrThread1_Out == NULL)
			perror("Error opening a file in thread 1\n");

	while(1)
	{
		sleep(10);																/*	Invokes the thread at every 10 secs*/

		fseek(fptrRead_File,iCount*1024,SEEK_SET);								/*	Seeks the position in file where it has left reading*/

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);		/*	Reads 1024 bytes from the file*/

			if(Read_Count < 1024)												/*	Check for EOF*/
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x50;										/*	Encryption*/
			}

			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread1_Out);	/*	Writing the encrypted data to the opened file */
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 1\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}


		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

		Thread1 .iPercent_Read = iCount * 1024 * 100 / lFile_Size ;				/*	Information is convayed to the Book keeping thread*/
		Thread1.iCount_Read = iCount;
		Thread1.iNum_Words = (int)Read_Count;

		pthread_cond_signal(&Thread1_Details);									/*	Signal the condition variable*/

		if(iBreak == 1)
			break;
		else if(Thread1.iBreak == 1)
			break;
	}

	fprintf(fptrThread1_Out,"\nEOF\n");											/*	Signals the reader that file has been read*/

	if(fclose(fptrThread1_Out) == EOF)											/*	Closing the opened file*/
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
	size_t 	Read_Count;															/*	Count of bytes that has been read from the file*/
	size_t 	Write_Count;														/*	Count of bytes that is about to written in the file*/
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int		iBreak = 0;															/*	Break variable indicates the end of the reading*/

	char	chBuffer[1200];

	fptrThread2_Out = fopen("Thread2_Data.txt","w");							/*	Open a file for writing encrypted data*/
	if(fptrThread2_Out == NULL)
		perror("Error opening a file in thread 2\n");


	while(iBreak == 0)
	{
		sleep(20);																/*	Invokes the thread at every 20 secs*/

		fseek(fptrRead_File,iCount*1024,SEEK_SET);								/*	Seeks the position in file where it has left reading*/

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);		/*	Reads 1024 bytes from the file*/

			if(Read_Count < 1024)												/*	Check for EOF*/
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x60;										/*	Encryption*/
			}
			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread2_Out);	/*	Writing the encrypted data to the opened file */
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 2\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}


		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

		Thread2.iPercent_Read = iCount * 1024 * 100 / lFile_Size ;				/*	Information is convayed to the Book keeping thread*/
		Thread2.iCount_Read = iCount;
		Thread2.iNum_Words = (int)Read_Count;

		pthread_cond_signal(&Thread2_Details);									/*	Signal the condition variable*/

		if(iBreak == 1)
			break;
		else if(Thread2.iBreak == 1)
			break;

	}

	fprintf(fptrThread2_Out,"\nEOF\n");											/*	Signals the reader that file has been read*/

	if(fclose(fptrThread2_Out) == EOF)											/*	Closing the opened file*/
	{
		perror("Error closing the file opened for writing data in thread 2\n");
	}

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
	size_t 	Read_Count;															/*	Count of bytes that has been read from the file*/
	size_t 	Write_Count;														/*	Count of bytes that is about to written in the file*/
	int		iCount = 0;															/*	Count for seeking a particular posistion in file*/
	int 	iLocal;
	int		iBreak = 0;															/*	Break variable indicates the end of the reading*/

	char	chBuffer[1200];

	fptrThread3_Out = fopen("Thread3_Data.txt","w");							/*	Open a file for writing encrypted data*/
	if(fptrThread3_Out == NULL)
		perror("Error opening a file in thread 3\n");

	while(1)
	{
		sleep(30);																/*	Invokes the thread at every 30 secs*/

		fseek(fptrRead_File,iCount*1024,SEEK_SET);								/*	Seeks the position in file where it has left reading*/

		if(iRead_Access > 0)
		{
			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access--;
			if(iRead_Access < 0)
				iRead_Access = 0;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/

			Read_Count = fread(chBuffer,sizeof(char),1024,fptrRead_File);		/*	Reads 1024 bytes from the file*/

			if(Read_Count < 1024)												/*	Check for EOF*/
				iBreak = 1;

			for(iLocal = 0; iLocal < Read_Count; iLocal++)
			{
				chBuffer[iLocal] += 0x70;										/*	Encryption*/
			}
			pthread_mutex_lock(&Lock_The_Access);								/*	Lock on the file access*/
			iRead_Access++;
			if(iRead_Access > 2)
				iRead_Access = 2;
			pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access*/
		}

		Write_Count = fwrite(chBuffer,sizeof(char),Read_Count,fptrThread3_Out);	/*	Writing the encrypted data to the opened file */
		if(Write_Count != Read_Count)
		{
			perror("Error in writing data to the file in Thread 3\n");
			printf("%d:Read, %d Written\n",(int)Read_Count,(int)Write_Count);
		}


		memset(chBuffer,0x00,sizeof(chBuffer));
		iCount++;

		Thread3.iPercent_Read = iCount * 1024 * 100 / lFile_Size ;				/*	Information is convayed to the Book keeping thread*/
		Thread3.iCount_Read = iCount;
		Thread3.iNum_Words = (int)Read_Count;

		pthread_cond_signal(&Thread3_Details);									/*	Signal the condition variable*/

		if(iBreak == 1)
			break;
		else if(Thread3.iBreak == 1)
			break;
	}

	fprintf(fptrThread3_Out,"\nEOF\n");											/*	Signals the reader that file has been read*/

	if(fclose(fptrThread3_Out) == EOF)											/*	Closing the opened file*/
	{
		perror("Error closing the file opened for writing data in thread 3\n");
	}

	printf("Terminating Thread3\n");
	pthread_exit(0);
}


/*
 * Function name	:	Book_Keeping_Thread
 *
 * Description		:	This function is used by the thread for book keeping purpose
 * 						like how much the given file is read, iteration count and
 * 						number of words read.
 *
 * Parameters		:	void *vptrDummy -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */
void *Book_Keeping_Thread(void *vptrDummy)
{
	FILE	*fptrBook_Keeping;													/*	Information about the threads*/

	fptrBook_Keeping = fopen("Book_Keeping.txt","w");
	if(fptrBook_Keeping == NULL)
		perror("Error opening a file Book keeping Thread\n");

	while(Thread3.iPercent_Read < 100)
	{
		if(Thread1.iPercent_Read < 100)
		{
			pthread_cond_wait(&Thread1_Details, &Lock_The_Access);				/*	Wait till the Condition variable is signled*/
			fprintf(fptrBook_Keeping,"Thread1:\n"
					"Percentage: %d%%, Iteration: %d, Number of Words: %d\n"
					,Thread1.iPercent_Read
					,Thread1.iCount_Read
					,Thread1.iNum_Words);
		}

		if(Thread2.iPercent_Read < 100)
		{
			pthread_cond_wait(&Thread2_Details, &Lock_The_Access);				/*	Wait till the Condition variable is signled*/
			fprintf(fptrBook_Keeping,"Thread2:\n"
					"Percentage: %d%%, Iteration: %d, Number of Words: %d\n"
					,Thread2.iPercent_Read
					,Thread2.iCount_Read
					,Thread2.iNum_Words);
		}

		if(Thread3.iPercent_Read < 100)
		{
			pthread_cond_wait(&Thread3_Details, &Lock_The_Access);				/*	Wait till the Condition variable is signled*/
			fprintf(fptrBook_Keeping,"Thread3:\n"
					"Percentage: %d%%, Iteration: %d, Number of Words: %d\n"
					,Thread3.iPercent_Read
					,Thread3.iCount_Read
					,Thread3.iNum_Words);
		}

		if(Thread1.iBreak == 1)
			break;
	}

	if(fclose(fptrBook_Keeping) == EOF)											/*	Closing the file opened for book keeping purpose*/
	{
		perror("Error closing the file opened for Book Keeping\n");
	}

	printf("Terminating the Book keeping thread\n");

	pthread_exit(0);
}


/*
 * Function name	:	Interrupt_Occured
 *
 * Description		:	This function is used by the SIGINT that is generated by
 * 						typing Ctrl+C in terminal. This function will end all the running
 * 						threads and the main function.
 *
 * Parameters		:	void *vptrDummy -> This is a dummy pointer does nothing
 *
 * Returns			:	None
 */
void Interrupt_Occured(int iSignal)
{
	printf("\nInterrupt has Occured you pressed %d\n",iSignal);			/*	Information to the user*/
	printf("Threads will terminate upon invokation\n");
	Thread1.iBreak = 1;													/*	Breaks the thread1*/
	Thread2.iBreak = 1;													/*	Breaks the thread2*/
	Thread3.iBreak = 1;													/*	Breaks the thread3*/
	iRead_Access = 3;													/*	Making this 3 will unblock any of the blocked thread*/
	pthread_mutex_unlock(&Lock_The_Access);								/*	Unlock the file access for the blocked thread*/
}
