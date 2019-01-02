/*
 * powerOf2BitWise.c
 *
 *  Created on: 26-Dec-2018
 *      Author: Parth shah
 */


#include<stdio.h>

#define bool int

/* Function to check if x is power of 2*/
bool isPowerOfTwo (int x)
{
  /* First x in the below expression is for the case when x is 0 */
  return x && (!(x&(x-1)));
}

/* Substraction bitwise*/
/*
 *     carry
 *      1/0 1 carry send 2 (1)
 *    0 1   1/0
 *  0 1 0   0
 * -0 0 0   1
 * -------------
 *  0 0 1   1
 * -------------
 *
 * */

/*Driver program to test above function*/
int main()
{
  isPowerOfTwo(1024)? printf("Yes\n"): printf("No\n");
  isPowerOfTwo(64)? printf("Yes\n"): printf("No\n");
  return 0;
}

