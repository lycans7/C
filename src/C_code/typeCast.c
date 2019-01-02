/*
 * typeCast.c
 *
 *  Created on: 24-Aug-2018
 *      Author: Parth shah
 */


#include <stdio.h>

int main(){
	int a = 257;
	char *ptr;
	int *iptr;
	iptr = ptr = &a;
	printf("%d %d\n", *(char *)ptr, *(char *)(ptr+1)); // 1,1
	printf("%d %d\n", *(char *)iptr, *(char *)(iptr+1)); // 1,garbage/(0)
	return 0;
}
