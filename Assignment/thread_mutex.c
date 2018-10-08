/*
 * thread_mutex.c
 *
 *  Created on: 19-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mut1;
pthread_mutex_t mut2;

void* integer() {
	int i;
	for (i = 1; i < 27; i++) {
		pthread_mutex_lock(&mut1);
		printf(" %d ", i);
		pthread_mutex_unlock(&mut2);

	}

}
void* character() {
	int i;
	char a = 'A';
	for (i = 1; i < 27; i++) {
		pthread_mutex_lock(&mut2);
		printf(" %c ", a++);
		pthread_mutex_unlock(&mut1);
	}

}
int main() {
	pthread_t t1, t2; //object of thread.

	printf("\n create thread and call function \n");

	pthread_create(&t1, NULL, integer, NULL); //thread create
	pthread_create(&t2, NULL, character, NULL);

	pthread_mutex_init(&mut1,NULL); // Initialization of mutex
	pthread_mutex_init(&mut2,NULL);

	pthread_join(t1, NULL); //wait for other thread to finished
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mut1); // destroy the mutex
	pthread_mutex_destroy(&mut2);
	printf("\n Destroy thread and call function \n");

	return 0;
}

