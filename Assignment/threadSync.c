/*
 * threadSync.c
 *
 *  Created on: 19-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2; //object of semaphore

void* integer() {
	int i;
	for (i = 1; i < 27; i++) {
		sem_wait(&sem1);
		printf(" %d ",i);
		sem_post(&sem2);
	}

}
void* character() {
	int i;
	char a = 'A';
	for (i = 1; i < 27; i++) {
		sem_wait(&sem2);
		printf(" %c ",a++);
		sem_post(&sem1);
	}

}

int main() {

	pthread_t t1, t2; //object of thread.

	printf("\n create thread and call function \n");

	pthread_create(&t1, NULL, integer, NULL); //thread create
	pthread_create(&t2, NULL, character, NULL);

	sem_init(&sem1, 0, 0);	//initialized semaphore
	sem_init(&sem2, 0, 1);
	sem_setprotocol(&sem2, SEM_PRIO_NONE);

	pthread_join(t1, NULL); //wait for other thread to finished
	pthread_join(t2, NULL);

	sem_destroy(&sem1); //destroy semaphore
	sem_destroy(&sem2);

	printf("\n Destroy thread and call function \n");
	return 0;
}
