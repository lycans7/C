/*
 * return_Scanf_printf.c
 *
 *  Created on: 19-Nov-2018
 *      Author: Parth shah
 */


#include <stdio.h>

int main(){
	int a,b,c;
	a = scanf("%d%d",&b,&c);
	b = printf("value of a %d \n",a);
	printf("%d",b);
	return 0;
}

