/*
 * swap_bits.c
 *
 *  Created on: 10-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main(){
	unsigned int val;
	int sw1,sw2;
	printf("\n Enter the value to swap \n");
	scanf("%x",&val);
	printf("\n Enter the position of bit want to swap 0-8 \n");
	scanf("%d %d",&sw1,&sw2);
	val ^= (1<<sw1);
	val ^= (1<<sw2);
	printf("\n After swap answer = x%02X \n",val);

}



