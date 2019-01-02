/*
 * test.c
 *
 *  Created on: 10-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int buff,i = 0,ptr;
	ptr = val;
	char res[10];
	while( ptr > 0){
		ptr = ptr/10;
		i++;
	}
	i--;
	while(val > 0){
		buff = val%10;
		res[i--] = buff + '0';
		val = val/10;
	}
	printf("\n buff == %d, val = %d , struct == %s ,line - %d \n",buff,val,res,__LINE__);
	return 0;
}
