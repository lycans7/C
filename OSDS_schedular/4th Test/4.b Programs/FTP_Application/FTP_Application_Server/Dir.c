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


extern int iStore;
extern char chFiles[20][70];


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
	DIR 	*dp;																/*	Holds the directory file descriptor*/
	struct dirent *Entry;														/*	File and directory names are accessed through this*/
	struct stat Statbuf;														/*	Type of file is accessed by this*/
	if((dp = opendir(chDir)) == NULL)											/*	Check if Specified directory is directory or not*/
	{
		 fprintf(stderr,"cannot open directory: %s\n", chDir);					/*	Error msg*/
		 return 0;
	}
	chdir(chDir);																/*	Step in to the specified directory*/
	while((Entry = readdir(dp)) != NULL)										/*	Reads the content of the directory*/
	{
		lstat(Entry->d_name,&Statbuf);
		if(S_ISDIR(Statbuf.st_mode))											/*	If the entry is directory*/
		{
			if(strcmp(".",Entry->d_name) == 0 ||								/*	Which directory is it*/
					strcmp("..",Entry->d_name) == 0)
				continue;														/*	Continue for scanning net entries*/
			else
				continue;
		}
		else
		{
			sprintf(chFiles[iStore],"%*s%s\n",iDepth,"",Entry->d_name);			/*	Converts the file entry in readable strings*/
			iStore++;															/*	Store the number of files*/
			if(iStore>20)														/*	If files are more than 20*/
				iStore = 0;														/*	Than make the counter 0*/
		}
	}
	chdir("..");																/*	Go back 1 step*/
	closedir(dp);																/*	Close the opened directory*/
	return 1;
}
