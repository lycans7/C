/*
 * Macro_swap_bitwise.c
 *
 *  Created on: 01-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#define SWAP(xp,yp)    xp = xp ^ yp; \
	                   yp = xp ^ yp;\
	                   xp = xp ^ yp;
int main()
{
int x = 10, y = 5;

SWAP(x,y);
printf("After Swapping: x = %d, y = %d", x, y);

return 0;
}



