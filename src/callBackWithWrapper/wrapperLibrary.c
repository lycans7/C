/*
 * wrapperLibrary.c
 *
 *  Created on: 12-Feb-2019
 *      Author: Parth shah
 */



#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

static int (*real_scanf)(const char* str) = NULL;

size_t strlen(const char *s){
	printf(" Hey ");
	printf("%s \n",s);
	real_scanf = dlsym(RTLD_NEXT, "strlen");
	return 0;
}
