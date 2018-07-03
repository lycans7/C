/*
 * imagec.c
 *
 *  Created on: 20-Jun-2018
 *      Author: eximiusdesign
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "Header.h"

#define FILENAME "Header.h"
#define FILENAME1 "Converted_Image.png"

sem_t semlock1,semlock2;
long sizeOfFile = 0;

void *ImageToHeader(void* arg) {

	sem_wait(&semlock1);

	FILE* getData, *writeData;

	getData = fopen("Captain.png", "r");

	if (getData != NULL) {
		printf("Successfull\n");
	} else {
		printf(" ERROR !! Unable to OPEN: %d\n", getData);
		return;
	}

	writeData = fopen(FILENAME, "w+");

	if (writeData != NULL) {
		printf("Successfull\n");
	} else {
		printf(" ERROR !! Unable to OPEN: %d\n", writeData);
		return;
	}

	fseek(getData, 0, SEEK_END);

	sizeOfFile = ftell(getData);
	fseek(getData, 0, SEEK_SET);

	if (sizeOfFile) {
		printf("%ld\n", sizeOfFile);
	} else {
		printf(" ERROR !! Unable to get size: %d\n", sizeOfFile);
		return;
	}
	int i = 0, count = 0;
	unsigned char c, arr[2];

	fputs("unsigned char America[] = { \n", writeData);
	fputs("\n \t\t\t", writeData);

	for (i = 0; i < sizeOfFile; i++) {
		if (i != sizeOfFile - 1) {
			c = fgetc(getData);
			sprintf(arr, "%d,", c);
			fputs(arr, writeData);
		} else {
			c = fgetc(getData);
			sprintf(arr, "%d", c);
			fputs(arr, writeData);
		}
		count++;
		if (count >= 20) {
			fputs("\n \t\t\t", writeData);
			count = 0;
		}

	}

	fputs("\n};", writeData);

	fclose(writeData);
	fclose(getData);

	sem_post(&semlock2);
}

void *HeaderToImage(void* arg) {
	sem_wait(&semlock2);
	int i, no_files=1, len=0;
	FILE *fp = NULL;

	for(i=0;i<no_files;i++)
	{
		fp = fopen(FILENAME1, "w+");
		if(fp==NULL)
		{
			printf("Unable to open file\n");
		}
		len = fwrite(America, 1, sizeOfFile, fp);
		printf("size:%d\n", len);
	}
	fclose(fp);

	sem_post(&semlock1);

}

void Image() {
	pthread_t thread1, thread2;
	int ret;
	ret = pthread_create(&thread1, NULL, ImageToHeader, NULL);

	if (ret != 0) {
		printf(" ERROR : Not able to create %d ", ret);
		return;
	}
	ret = pthread_create(&thread2, NULL, HeaderToImage, NULL);
	if (ret != 0) {
		printf(" ERROR : Not able to create %d ", ret);
		return;
	}
	sem_init(&semlock1, 0, 1);
	sem_init(&semlock2, 0, 0);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	sem_destroy(&semlock1);
	sem_destroy(&semlock2);

}

