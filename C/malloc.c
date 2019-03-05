#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>

//#define SIZE 10
void *malloc_own(int size,int *);
void *own_free(int *);
int main()
{
	int *p,*q;
	p = malloc_own(10,q);
	printf("val at the addr in main = %d\n",*p);
	int *t = (int*)malloc(sizeof(int));
	q = own_free(p);
	printf("val at the addr in main = %p\n ",q);
	return 0;
}

void *malloc_own(int size,int *plen)
{
	int val;
	int len = size * sizeof( size ); // Add sizeof( size ) for holding length.

	plen = mmap( 0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
	if(plen == NULL)
	{
		printf("No mapping \n");
		exit(100);
	}
	printf("Addr = %p\n val at addr = %d\n",plen,*plen);
	scanf("%d",&val);
	int *s = (int*)malloc(sizeof(int));	

	*plen = val;                     // First 4 bytes contain length.
	return (void*)(plen); 
}

void *own_free(int *plen)
{
	int len;
    	len = *plen;                     // Read length

//	plen--;                          // Reach top of memory

    	munmap( (void*)plen, len );
	printf("Memory is free :\n");
	printf("Addr = %p\n ",plen);
	return (void *)plen;
}

