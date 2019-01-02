/*
 * basicSignalHandler.c
 *
 *  Created on: 24-Jul-2018
 *      Author: Parth shah
 */

/* *********** change the behaviour of default SIGINT************ */

#include <signal.h>

void changeSignal(){
	printf("\n I change the signal 2 with print \n");
}

int main(){

	signal(SIGINT,changeSignal); //change the property of default SIGINT to another function.
	//getchar(); //used instead of while(1) after generate signal while enter char, you will see
	// signal first show the value come that means signal will generate anyhow
	while(1);//
	return 0;
}
