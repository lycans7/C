/*
 * constants_before_pointer.c
 *
 *  Created on: 24-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main(){
	int const *p; // pointer can point to another address , value can't (read only.)
	int a = 2,b = 5;
//	int const *q = 5; // can't assign value to pointer directly. segmentation fault
	int const *r = &a; //same as first *p , and assign address.

	printf("\n %d LINE %d \n",*p,__LINE__);
//	*p = a; // can't give like this 	//compilation time error.
	printf("\n %d LINE %d \n",*p,__LINE__);
	p = &a;
	printf("\n %d LINE %d \n",*p,__LINE__);

//	printf("\n %d LINE %d \n",*q,__LINE__);
//	*q = a; // can't give like this
//	printf("\n %d LINE %d \n",*q,__LINE__);
//	q = &a;
//	printf("\n %d LINE %d \n",*q,__LINE__);


	printf("\n %d LINE %d \n",*r,__LINE__);
//	*r = b; // can't give like this
	printf("\n %d LINE %d \n",*r,__LINE__);
	r = &b;
	printf("\n %d LINE %d \n",*r,__LINE__);
	return 0;
}


