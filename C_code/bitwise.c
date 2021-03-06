/*
 * bitwise.c
 *
 *  Created on: 06-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>

/**** Integer (~)Note if operation perform with another bitwise operator then ******
 ****** 1's complement takes***************/
main() {

   unsigned int a = 9;	/* 60 = 0011 1100 */
   unsigned int b = 13;	/* 13 = 0000 1101 */
   int c = 0;

   c = a & b;       /* 12 = 0000 1100 */
   printf("Line 1 - Value of c is %d\n", c );

   c = a | b;       /* 61 = 0011 1101 */
   printf("Line 2 - Value of c is %d\n", c );

   c = a ^ b;       /* 49 = 0011 0001 */
   printf("Line 3 - Value of c is %d\n", c );

   c = ~a;          /*-61 = 1100 0011 */
   printf("Line 4 - Value of c is %d %d %d %d\n",c,a,~a, a= ~a );

   c = a << 2;     /* 240 = 1111 0000 */
   printf("Line 5 - Value of c is %d\n", c );

   c = a >> 2;     /* 15 = 0000 1111 */
   printf("Line 6 - Value of c is %d\n", c );

   c = a & ~(a-1);     /* 15 = 0000 1111 */
   printf("Line 6 - Value of c is %d\n", c );

}
