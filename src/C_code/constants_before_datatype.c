/*
 * constants_before_datatype.c
 *
 *  Created on: 24-Aug-2018
 *      Author: Parth shah
 */

#include<stdio.h>
void hello(int a) { printf("hello %d \n",a); }
int main(void) {
(**********hello)(5);
}
