/**
 * @file main.c
 * @author Tejas prajapati
 * @date 14-08-15
 * @brief File containing Program Telephone ticket booking
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<pthread.h>
#include	<semaphore.h>
#include	<time.h>

/*
 * @brief Macros for the Shorter and faster operation
 *
 * TFPERCENT means the 25% of a where a is passed in
 * when the program is executing
 *
 * FPERCENT means the 50% of a where a is passed in
 * when the program is executing
 *
 * SFPERCENT means the 75% of a where a is passed in
 * when the program is executing
 *
 * HPERCENT means the 100% of a where a is passed in
 * when the program is executing
 *
 * The last one is MAX_SEATS which defines a maximum
 * value of the seats that a plane contain
 */
#define 	TFPERCENT(a)		(a*25/100)										/**<25% of what is passed in*/
#define 	FPERCENT(a)			(a*50/100)										/**<50% of what is passed in*/
#define 	SFPERCENT(a)		(a*75/100)										/**<75% of what is passed in*/
#define		HPERCENT(a)			(a)												/**<100% of what is passed in*/
#define		MAX_SEATS			200												/**<Maximum number of seats*/

/*
 * @brief	Variable declaration
 *
 * iSeats 				maximum available seats
 * iCaller				number of callers currently online
 * iOnce				process control variable
 * iBook_Thread_Called	indication of the called thread
 */
int 			iSeats = MAX_SEATS;												/**<Allocate the seats*/
int 			iCaller = 0;													/**<Initialize the caller queue*/
int				iOnce;															/**<Variable used for printing book keeping info*/
int				iBook_Thread_Called = 0;										/**<Varible used for printing book keeping info*/


/*
 * @brief	Variable declaration
 *
 * Result_Threads 		thread variables used by the linux system
 * 						for context switching
 * *vptrThread_Results	results of thread joining
 */
pthread_t 		Result_Threads[6];												/**<Array of thread results*/
void 			*vptrThread_Results[6];											/**<Thread joining result array*/



/*
 * @brief	Variable declaration
 *
 * Lock_Seats 		mutex variable
 * *Seat_Condition	condition variable
 */
pthread_mutex_t Lock_Seats = PTHREAD_MUTEX_INITIALIZER;							/**<Mutex declaration and intialization*/
pthread_cond_t 	Seat_Condition = PTHREAD_COND_INITIALIZER;						/**<Condition variable declaration and initialization*/



/*
 * @brief	Function declaration
 *
 * Agent1 		Thread function
 * Agent2		Thread function
 * Agent3		Thread function
 * Agent4		Thread function
 * Agent5		Thread function
 * Book_Keeping	Thread function
 */
void 			*Agent1(void *);												/**<Function declaration of one of the Agent threads*/
void 			*Agent2(void *);												/**<Function declaration of one of the Agent threads*/
void 			*Agent3(void *);												/**<Function declaration of one of the Agent threads*/
void 			*Agent4(void *);												/**<Function declaration of one of the Agent threads*/
void 			*Agent5(void *);												/**<Function declaration of one of the Agent threads*/
void 			*Book_Keeping(void *);											/**<Function declaration of book keeping thread*/



/*
 * @brief Ticket Booking program starts from here
 * @param [IN] None
 * 		  [OUT] 0 on success and 1 on failure
 *
 * This is the main function of Telephone Ticket Booking system.
 * This function declares Result variables of the threads.
 *
 * This function calls the supporting functions to perform the
 * task of Booking system. Functions that are called in this function
 * are like pthread_create() and pthread_join().
 *
 * Agentx and Book_Keeping functions are user defined functions
 * That are called from the threads.
 *
 * fsync() is  also called in this function to perform the
 * requirement of system with proper output at proper time.
 *
 * This function prints the user info on the screen.
 *
 * This function as is the only main function creates Threads
 * for 5 different agents and a book keeping purpose.
 */
int main()
{
	int iResult[6];																/**<Result variable holds thread generation results*/

	iResult[0] = pthread_create(&Result_Threads[0],NULL,Agent1,NULL);			/**<Create a thread for agent 1*/
	if(iResult[0] != 0)
		perror("Agent1 thread creation failed");								/**<Error message*/

	iResult[1] = pthread_create(&Result_Threads[1],NULL,Agent2,NULL);			/**<Create a thread for agent 2*/
	if(iResult[1] != 0)
		perror("Agent1 thread creation failed");								/**<Error message*/

	iResult[2] = pthread_create(&Result_Threads[2],NULL,Agent3,NULL);			/**<Create a thread for agent 3*/
	if(iResult[2] != 0)
		perror("Agent1 thread creation failed");								/**<Error message*/

	iResult[3] = pthread_create(&Result_Threads[3],NULL,Agent4,NULL);			/**<Create a thread for agent 4*/
	if(iResult[3] != 0)
		perror("Agent1 thread creation failed");								/**<Error message*/

	iResult[4] = pthread_create(&Result_Threads[4],NULL,Agent5,NULL);			/**<Create a thread for agent 5*/
	if(iResult[4] != 0)
		perror("Agent1 thread creation failed");								/**<Error message*/

	iResult[5] = pthread_create(&Result_Threads[5],NULL,Book_Keeping,NULL);		/**<Create a thread for Book keeping function*/
	if(iResult[5] != 0)
	{
		perror("Book keeping thread creation failed");							/**<Error message*/
		exit(EXIT_FAILURE);														/**<Exit as the functionality will be void*/
	}

	while(1)
	{
		printf("Press enter to generate a call\n");								/**<User information*/
		fsync(1);																/**<Sync with the stdout*/
		getchar();																/**<Get a call*/
		fsync(0);																/**<Sync with the stdin*/
		if(iSeats == 0)															/**<If seats are all booked*/
			break;																/**<Break the loop*/
		if(iBook_Thread_Called == 0)											/**<If book keeping thread is busy do not enter the loop*/
		{
			iCaller++;															/**<Increament the caller*/
			printf("Callers available %d\n",iCaller);							/**<User information of queue*/
			fsync(1);															/**<Sync with the stdout*/
		}
	}

	iResult[0] = pthread_join(Result_Threads[0],&vptrThread_Results[0]);		/**<Join the threads as all the seats are booked*/
	if(iResult[0] != 0)
		perror("Error joining the thread");										/**<Error message*/
	printf("Sorry booking is full\n");											/**<User information*/

	iResult[1] = pthread_join(Result_Threads[1],&vptrThread_Results[1]);		/**<Join the thread*/
	if(iResult[1] != 0)
		perror("Error joining the thread");										/**<Error message*/

	iResult[2] = pthread_join(Result_Threads[2],&vptrThread_Results[2]);		/**<Join the thread*/
	if(iResult[2] != 0)
		perror("Error joining the thread");										/**<Error message*/

	iResult[3] = pthread_join(Result_Threads[3],&vptrThread_Results[3]);		/**<Join the thread*/
	if(iResult[3] != 0)
		perror("Error joining the thread");										/**<Enter message*/

	iResult[4] = pthread_join(Result_Threads[4],&vptrThread_Results[4]);		/**<Join the thread*/
	if(iResult[4] != 0)
		perror("Error joining the thread");										/**<Error message*/

	iResult[5] = pthread_join(Result_Threads[5],&vptrThread_Results[5]);		/**<Join the thread*/
	if(iResult[5] != 0)
		perror("Error joining the thread");										/**<Error message*/

	exit(EXIT_SUCCESS);															/**<Exit with success*/
}


/*
 * @brief	Agent1 books the ticket for the picked callers
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is one of the 5 agents which books the tickets
 * for the XYZ airline's 200 seater plane. This function also
 * informs the Book_Keeping thread at the completion of 25%,
 * 50%, 75% and 100% booking.
 */
void *Agent1(void *vptrDummy)
{
	int iBook;																	/**<Variable that holds the number of tickets to be booked*/
	int iSleep_Time;															/**<Sleep time variable*/
	int	iBreak_Time = 0;														/**<Break time variable*/
	while(iSeats > 0)															/**<While the seats are available loop*/
	{
		if(iCaller > 0 && iBook_Thread_Called == 0)								/**<If caller is available and Book keeping thread is not busy*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the available seats*/
			iCaller--;															/**<Pick up a call*/
			if(iCaller < 0)														/**<Making the code error prone*/
			{
				iCaller = 0;													/**<By making the available callers to 0 if it has become negative*/
				pthread_mutex_unlock(&Lock_Seats);								/**<Unlock the seats*/
				continue;														/**<Do not go beyonf this*/
			}
			iBook = rand() % 5;													/**<Book random seats*/
			if(iBook > iSeats)													/**<If seats not more than the amount to be booked*/
				iBook = iSeats;													/**<Then make the available seats as booked seats*/
			else if(iBook == 0)													/**<If booked seats are 0*/
				iBook = 1;														/**<Then make it one for successful call*/
			iSeats -= iBook;													/**<Decreament the seats by the booked seats*/
			if(iSeats == 0)														/**<If seats are all booked */
				iBreak_Time = 1;												/**<Then set for break the loop*/
			iSleep_Time = rand() % 10;											/**<Set the time for sleep of time between 0 to 9 seconds*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the available seats*/
			sleep(iSleep_Time);													/**<Sleep as above calculated time*/
			printf("Agent 1 Booked seats %d, time taken %d seconds\n"			/**<User information*/
					, iBook, iSleep_Time);
			fsync(1);															/**<Sync with stdout*/
		}

		if(iSeats <= (MAX_SEATS-TFPERCENT(MAX_SEATS)) && iOnce == 0)			/**<If booking has reached 25%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 1;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Now the Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-FPERCENT(MAX_SEATS)) && iOnce == 1)		/**<If booking has reached 50%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 2;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-SFPERCENT(MAX_SEATS)) && iOnce == 2)		/**<If booking has reached 75%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 3;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-HPERCENT(MAX_SEATS)) && iOnce == 3)		/**<If booking has reached 100%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 4;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
			if(iBreak_Time == 1)												/**<If break time variable has been set*/
				break;															/**<Then break the loop*/
		}
	}
	pthread_exit(0);															/**<Safely exit from the thread*/
}


/*
 * @brief	Agent2 books the ticket for the picked callers
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is one of the 5 agents which books the tickets
 * for the XYZ airline's 200 seater plane. This function also
 * informs the Book_Keeping thread at the completion of 25%,
 * 50%, 75% and 100% booking.
 */
void *Agent2(void *vptrDummy)
{
	int iBook;																	/**<Variable that holds the number of tickets to be booked*/
	int iSleep_Time;															/**<Sleep time variable*/
	int	iBreak_Time = 0;														/**<Break time variable*/
	while(iSeats > 0)															/**<While the seats are available loop*/
	{
		if(iCaller > 0 && iBook_Thread_Called == 0)								/**<If caller is available and Book keeping thread is not busy*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the available seats*/
			iCaller--;															/**<Pick up a call*/
			if(iCaller < 0)														/**<Making the code error prone*/
			{
				iCaller = 0;													/**<By making the available callers to 0 if it has become negative*/
				pthread_mutex_unlock(&Lock_Seats);								/**<Unlock the seats*/
				continue;														/**<Do not go beyonf this*/
			}
			iBook = rand() % 5;													/**<Book random seats*/
			if(iBook > iSeats)													/**<If seats not more than the amount to be booked*/
				iBook = iSeats;													/**<Then make the available seats as booked seats*/
			else if(iBook == 0)													/**<If booked seats are 0*/
				iBook = 1;														/**<Then make it one for successful call*/
			iSeats -= iBook;													/**<Decreament the seats by the booked seats*/
			if(iSeats == 0)														/**<If seats are all booked */
				iBreak_Time = 1;												/**<Then set for break the loop*/
			iSleep_Time = rand() % 10;											/**<Set the time for sleep of time between 0 to 9 seconds*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the available seats*/
			sleep(iSleep_Time);													/**<Sleep as above calculated time*/
			printf("Agent 2 Booked seats %d, time taken %d seconds\n"			/**<User information*/
					, iBook, iSleep_Time);
			fsync(1);															/**<Sync with stdout*/
		}

		if(iSeats <= (MAX_SEATS-TFPERCENT(MAX_SEATS)) && iOnce == 0)			/**<If booking has reached 25%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 1;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Now the Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-FPERCENT(MAX_SEATS)) && iOnce == 1)		/**<If booking has reached 50%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 2;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-SFPERCENT(MAX_SEATS)) && iOnce == 2)		/**<If booking has reached 75%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 3;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-HPERCENT(MAX_SEATS)) && iOnce == 3)		/**<If booking has reached 100%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 4;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
			if(iBreak_Time == 1)												/**<If break time variable has been set*/
				break;															/**<Then break the loop*/
		}
	}
	pthread_exit(0);															/**<Safely exit from the thread*/
}


/*
 * @brief	Agent3 books the ticket for the picked callers
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is one of the 5 agents which books the tickets
 * for the XYZ airline's 200 seater plane. This function also
 * informs the Book_Keeping thread at the completion of 25%,
 * 50%, 75% and 100% booking.
 */
void *Agent3(void *vptrDummy)
{
	int iBook;																	/**<Variable that holds the number of tickets to be booked*/
	int iSleep_Time;															/**<Sleep time variable*/
	int	iBreak_Time = 0;														/**<Break time variable*/
	while(iSeats > 0)															/**<While the seats are available loop*/
	{
		if(iCaller > 0 && iBook_Thread_Called == 0)								/**<If caller is available and Book keeping thread is not busy*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the available seats*/
			iCaller--;															/**<Pick up a call*/
			if(iCaller < 0)														/**<Making the code error prone*/
			{
				iCaller = 0;													/**<By making the available callers to 0 if it has become negative*/
				pthread_mutex_unlock(&Lock_Seats);								/**<Unlock the seats*/
				continue;														/**<Do not go beyonf this*/
			}
			iBook = rand() % 5;													/**<Book random seats*/
			if(iBook > iSeats)													/**<If seats not more than the amount to be booked*/
				iBook = iSeats;													/**<Then make the available seats as booked seats*/
			else if(iBook == 0)													/**<If booked seats are 0*/
				iBook = 1;														/**<Then make it one for successful call*/
			iSeats -= iBook;													/**<Decreament the seats by the booked seats*/
			if(iSeats == 0)														/**<If seats are all booked */
				iBreak_Time = 1;												/**<Then set for break the loop*/
			iSleep_Time = rand() % 10;											/**<Set the time for sleep of time between 0 to 9 seconds*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the available seats*/
			sleep(iSleep_Time);													/**<Sleep as above calculated time*/
			printf("Agent 3 Booked seats %d, time taken %d seconds\n"			/**<User information*/
					, iBook, iSleep_Time);
			fsync(1);															/**<Sync with stdout*/
		}

		if(iSeats <= (MAX_SEATS-TFPERCENT(MAX_SEATS)) && iOnce == 0)			/**<If booking has reached 25%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 1;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Now the Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-FPERCENT(MAX_SEATS)) && iOnce == 1)		/**<If booking has reached 50%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 2;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-SFPERCENT(MAX_SEATS)) && iOnce == 2)		/**<If booking has reached 75%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 3;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-HPERCENT(MAX_SEATS)) && iOnce == 3)		/**<If booking has reached 100%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 4;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
			if(iBreak_Time == 1)												/**<If break time variable has been set*/
				break;															/**<Then break the loop*/
		}
	}
	pthread_exit(0);															/**<Safely exit from the thread*/
}


/*
 * @brief	Agent4 books the ticket for the picked callers
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is one of the 5 agents which books the tickets
 * for the XYZ airline's 200 seater plane. This function also
 * informs the Book_Keeping thread at the completion of 25%,
 * 50%, 75% and 100% booking.
 */
void *Agent4(void *vptrDummy)
{
	int iBook;																	/**<Variable that holds the number of tickets to be booked*/
	int iSleep_Time;															/**<Sleep time variable*/
	int	iBreak_Time = 0;														/**<Break time variable*/
	while(iSeats > 0)															/**<While the seats are available loop*/
	{
		if(iCaller > 0 && iBook_Thread_Called == 0)								/**<If caller is available and Book keeping thread is not busy*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the available seats*/
			iCaller--;															/**<Pick up a call*/
			if(iCaller < 0)														/**<Making the code error prone*/
			{
				iCaller = 0;													/**<By making the available callers to 0 if it has become negative*/
				pthread_mutex_unlock(&Lock_Seats);								/**<Unlock the seats*/
				continue;														/**<Do not go beyonf this*/
			}
			iBook = rand() % 5;													/**<Book random seats*/
			if(iBook > iSeats)													/**<If seats not more than the amount to be booked*/
				iBook = iSeats;													/**<Then make the available seats as booked seats*/
			else if(iBook == 0)													/**<If booked seats are 0*/
				iBook = 1;														/**<Then make it one for successful call*/
			iSeats -= iBook;													/**<Decreament the seats by the booked seats*/
			if(iSeats == 0)														/**<If seats are all booked */
				iBreak_Time = 1;												/**<Then set for break the loop*/
			iSleep_Time = rand() % 10;											/**<Set the time for sleep of time between 0 to 9 seconds*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the available seats*/
			sleep(iSleep_Time);													/**<Sleep as above calculated time*/
			printf("Agent 4 Booked seats %d, time taken %d seconds\n"			/**<User information*/
					, iBook, iSleep_Time);
			fsync(1);															/**<Sync with stdout*/
		}

		if(iSeats <= (MAX_SEATS-TFPERCENT(MAX_SEATS)) && iOnce == 0)			/**<If booking has reached 25%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 1;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Now the Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-FPERCENT(MAX_SEATS)) && iOnce == 1)		/**<If booking has reached 50%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 2;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-SFPERCENT(MAX_SEATS)) && iOnce == 2)		/**<If booking has reached 75%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 3;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-HPERCENT(MAX_SEATS)) && iOnce == 3)		/**<If booking has reached 100%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 4;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
			if(iBreak_Time == 1)												/**<If break time variable has been set*/
				break;															/**<Then break the loop*/
		}
	}
	pthread_exit(0);															/**<Safely exit from the thread*/
}


/*
 * @brief	Agent5 books the ticket for the picked callers
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is one of the 5 agents which books the tickets
 * for the XYZ airline's 200 seater plane. This function also
 * informs the Book_Keeping thread at the completion of 25%,
 * 50%, 75% and 100% booking.
 */
void *Agent5(void *vptrDummy)
{
	int iBook;																	/**<Variable that holds the number of tickets to be booked*/
	int iSleep_Time;															/**<Sleep time variable*/
	int	iBreak_Time = 0;														/**<Break time variable*/
	while(iSeats > 0)															/**<While the seats are available loop*/
	{
		if(iCaller > 0 && iBook_Thread_Called == 0)								/**<If caller is available and Book keeping thread is not busy*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the available seats*/
			iCaller--;															/**<Pick up a call*/
			if(iCaller < 0)														/**<Making the code error prone*/
			{
				iCaller = 0;													/**<By making the available callers to 0 if it has become negative*/
				pthread_mutex_unlock(&Lock_Seats);								/**<Unlock the seats*/
				continue;														/**<Do not go beyonf this*/
			}
			iBook = rand() % 5;													/**<Book random seats*/
			if(iBook > iSeats)													/**<If seats not more than the amount to be booked*/
				iBook = iSeats;													/**<Then make the available seats as booked seats*/
			else if(iBook == 0)													/**<If booked seats are 0*/
				iBook = 1;														/**<Then make it one for successful call*/
			iSeats -= iBook;													/**<Decreament the seats by the booked seats*/
			if(iSeats == 0)														/**<If seats are all booked */
				iBreak_Time = 1;												/**<Then set for break the loop*/
			iSleep_Time = rand() % 10;											/**<Set the time for sleep of time between 0 to 9 seconds*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the available seats*/
			sleep(iSleep_Time);													/**<Sleep as above calculated time*/
			printf("Agent 5 Booked seats %d, time taken %d seconds\n"			/**<User information*/
					, iBook, iSleep_Time);
			fsync(1);															/**<Sync with stdout*/
		}

		if(iSeats <= (MAX_SEATS-TFPERCENT(MAX_SEATS)) && iOnce == 0)			/**<If booking has reached 25%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 1;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Now the Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-FPERCENT(MAX_SEATS)) && iOnce == 1)		/**<If booking has reached 50%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 2;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-SFPERCENT(MAX_SEATS)) && iOnce == 2)		/**<If booking has reached 75%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 3;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
		}
		else if(iSeats <= (MAX_SEATS-HPERCENT(MAX_SEATS)) && iOnce == 3)		/**<If booking has reached 100%*/
		{
			pthread_mutex_lock(&Lock_Seats);									/**<Lock the access to the seats*/
			iOnce = 4;															/**<Increament the variable so that this condition is called only once*/
			iBook_Thread_Called = 1;											/**<Book keeping thread will be called*/
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seats*/
			pthread_cond_signal(&Seat_Condition);								/**<Signal the book keeping thread*/
			if(iBreak_Time == 1)												/**<If break time variable has been set*/
				break;															/**<Then break the loop*/
		}
	}
	pthread_exit(0);															/**<Safely exit from the thread*/
}


/*
 * @brief	Book_Keeping function keeps the track of the tickets
 * @param	void *vptrDummy is a dummy pointer of type void
 * 			which is used nowhere in the program
 * @retval	void * returns NULL if successfully exited from the
 * 			thread
 *
 * This function is keeping track of how many seats are booked.
 * This function also informs the user at the completion of 25%,
 * 50%, 75% and 100%. This informations are passed from the
 * agents for which the thread function is waiting.
 */
void *Book_Keeping(void *vptrDummy)
{
	while(1)
	{
		pthread_cond_wait(&Seat_Condition,&Lock_Seats);							/**<Wait till one of the agents signal*/
		printf("%d%% Seats are booked"											/**<Print the user information*/
			",Availabled Seats are %d\n",
			((MAX_SEATS-iSeats)*100/MAX_SEATS),iSeats);
		if(iSeats == 0)															/**<If seats are all booked*/
		{
			pthread_mutex_unlock(&Lock_Seats);									/**<Unlock the access to the seat for safety*/
			break;																/**<Break the loop*/
		}
		iBook_Thread_Called = 0;												/**<Book keeping thread has finished its work indication*/
	}
	pthread_exit(0);															/**<Exit from the thread safely*/
}
