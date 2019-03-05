/*
 * main.c
 *
 *  Created on: 20-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include	<unistd.h>
#include 	<dirent.h>
#include 	<string.h>
#include 	<sys/stat.h>
#include 	<stdlib.h>
#include	"Dir.h"
#include	"Hash.h"



int iStore;
int iSize_Of_Table = 10;
int iNumber_Of_Lines = 20;
char chFiles[10][MAX_LENGTH_OF_FILE];
char chFull_Path[70];
char chSearch_String[200];



int main()
{
	int iLocal,iInternal,iSuccess;
	Hash_Table_p File_Hash_Table;
	Hash_Table_C_p File_Contents_Hash_Table;

	while(1)
	{
		printf("For Directory scan please provide the full path:\n");
		scanf("%s",chFull_Path);

		iSuccess = Get_Dir(chFull_Path,0);
		if(iSuccess == 0)
		{
			printf("Please provide a directory for scan/n");
			continue;
		}
		else
			break;
	}

	for(iLocal=0;iLocal<iStore;iLocal++)
		printf("%s",chFiles[iLocal]);

	for(iLocal=0;iLocal<iStore;iLocal++)
		for(iInternal=0;iInternal<MAX_LENGTH_OF_FILE;iInternal++)
			if(chFiles[iLocal][iInternal]=='\n')
				chFiles[iLocal][iInternal] = '\0';


	File_Hash_Table = Create_Hash_Table(iSize_Of_Table);

	File_Contents_Hash_Table = Create_Hash_Table(iNumber_Of_Lines);


	for(iLocal = 0;iLocal<iStore;iLocal++)
		Get_File(chFiles[iLocal],chFull_Path,&File_Contents_Hash_Table);


	for(iLocal = 0;iLocal<iStore;iLocal++)
		Add_File(File_Hash_Table,chFiles[iLocal]);

	printf("Please Provide a Complete line from a file to search: ");
	getchar();
	fgets(chSearch_String, 200, stdin);

	Print_File_Hash_Table(File_Contents_Hash_Table,chSearch_String);
	Print_Hash_Table(File_Hash_Table);

	printf("Terminating.....\n");
	Free_Table(File_Hash_Table);
	Free_Table(File_Contents_Hash_Table);
	return 0;
}
