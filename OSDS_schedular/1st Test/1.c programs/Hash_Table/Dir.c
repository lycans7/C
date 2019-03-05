/*
 * Dir.c
 *
 *  Created on: 17-Jul-2015
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


extern int iStore;
extern char chFiles[10][70];


/*
 * Function name	:	Get_Dir
 *
 * Description		:	use this function to read the contents of the file and
 * 						hash the string in to the hash table using Add_String()
 *
 * Parameters		:	char *chDir -> directory path which we need to open
 * 						int iDepth -> depth is the key its meaning is how deep
 * 									  the directory is needed to be open
 *
 * Returns			:	1 if successfull in opening the directory else 0
 */
int Get_Dir(char *chDir, int iDepth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(chDir)) == NULL)
	{
		 fprintf(stderr,"cannot open directory: %s\n", chDir);
		 return 0;
	}
	chdir(chDir);
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			/* Found a directory, but ignore . and .. */
			if(strcmp(".",entry->d_name) == 0 ||
					strcmp("..",entry->d_name) == 0)
				continue;
			else
				continue;
		}
		else
		{
			sprintf(chFiles[iStore],"%*s%s\n",iDepth,"",entry->d_name);
			iStore++;
			if(iStore>10)
				iStore = 0;
		}
	}
	chdir("..");
	closedir(dp);
	return 1;
}


/*
 * Function name	:	Get_File
 *
 * Description		:	use this function to read the contents of the file and
 * 						hash the string in to the hash table using Add_String()
 *
 * Parameters		:	char *chFile_Name -> file name which we need to read
 * 						char * chPath -> full path of a file where the file is located
 * 										 Hash_Table_C_p *Hash_Table -> pointer to the
 * 										 hash table in which the hashed values of the strings are added.
 *
 * Returns			:	None
 */
void Get_File(char *chFile_Name,char * chPath, Hash_Table_C_p *Hash_Table)
{
	char chString[150];															/*full path with filename will be hold in this string*/
	char chRead_String[100][200];												/*file will be read in this string*/
	int iLine_Count = 0;														/*to count the line number in a file*/
	int iLocal = 0;																/*to count the character in a file*/

	FILE *Read_File = NULL;														/*file pointer to open or read a particular file*/

	strcpy(chString,chPath);
	strcat(chString,"/");
	strcat(chString,chFile_Name);

	Read_File = fopen(chString,"r");
	if(Read_File != NULL)
	{
		chRead_String[iLine_Count][iLocal++] = fgetc(Read_File);
		while(chRead_String[iLine_Count][iLocal] != EOF)
		{
			if(chRead_String[iLine_Count][iLocal-1] == '\n')
			{
				Add_String(*Hash_Table,chString,chRead_String[iLine_Count],iLine_Count);
				iLine_Count++;
				iLocal = 0;
			}
			if(feof(Read_File))
				break;

			chRead_String[iLine_Count][iLocal++] = fgetc(Read_File);
		}
		Add_String(*Hash_Table,chString, chRead_String[iLine_Count],iLine_Count);
	}
}
