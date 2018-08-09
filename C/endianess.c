/*
 * endianess.c
 *
 *  Created on: 07-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main(){

	unsigned int i = 1<<7; // till 7 it is gives little , 8 onwards bit endian . since system is little endian.
	char* ptr = (char *)&i; // Since size of character is 1 byte when the character pointer is de-referenced
							// it will contain only first byte of integer
	if(*ptr){
		printf("\n Little endian \n");
	}else{
		printf("\n Big endian \n");
	}
	getchar();
	return 0;
}


