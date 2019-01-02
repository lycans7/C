/*
 * ownMallocFree.c
 *
 *  Created on: 12-Dec-2018
 *      Author: Parth shah
 */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void* my_Malloc(size_t size);
void my_Free(void* ptr);

int main() {
	int *ptr = (int*) my_Malloc(10);
	*ptr = 20;
	printf("%d", *ptr);
	my_Free(ptr);
	return 0;
}

void* my_Malloc(size_t size) {
	void* mem = NULL;
	int len = size * sizeof(size);
	mem = mmap(0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,
			0);
	if (mem == (void *) -1) {
		printf(" \n ERROR:: MEMORY NOT AVAILABLE \n");
		return 1;
	}
	return mem;
}
void my_Free(void* ptr) {
	int size;
	size = *(int*) ptr;
	munmap((void*) ptr, size);
	printf("Memory is free :\n");
}

