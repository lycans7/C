/*
 * FPT_App_Client.c
 *
 *  Created on: 06-Aug-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include 	<dirent.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include 	<sys/types.h>
#include	<time.h>



char		chOption_Buffer[15];												/*	Checks the options selected by client*/


typedef struct sockaddr_in Socket_t;											/*	Structure is renamed for shorter name in program*/


void 	Print_Info(void);														/*	Prints the Basic information regarding the options available*/


int main()
{
	char		chPWD[150];														/*	Working directory*/
	char		chFile_Path[300];												/*	File path*/
	int			iSockfd;														/*	Socket descriptor*/
	int			iStr_Len;														/*	Length of file path*/
	int 		iResult;														/*	Result of server client connection*/
	int			iLen;															/*	Length of Client address*/
	int 		iRead;															/*	Holds the count of bytes that are written to file*/
	char 		chBuffer[2048];													/*	Buffer data*/
	char		*chptrTemp_Buf = NULL;											/*	Temporary buffer*/
	Socket_t 	Client_Address;													/*	Client adderss socket*/
	FILE		*fptrDownloads = NULL;											/*	File pointer for downloaded files*/

	memset(chBuffer,0x00,sizeof(chBuffer));										/*	Cleans the all buffers*/
	memset(chFile_Path,0x00,sizeof(chFile_Path));
	memset(chPWD,0x00,sizeof(chPWD));

	if(getcwd(chPWD,150) == NULL)												/*	Get the current directory*/
		fprintf(stderr,"Error in reading the current directory.\n");

	strcat(chPWD,"/Downloads");													/*	Store the information in Buffer*/
	strcpy(chFile_Path,chPWD);													/*	Copy the Information for creating files in that directory*/
	strcat(chFile_Path,"/");													/*	Add the '/' for stepping in*/
	iStr_Len = strlen(chFile_Path);												/*	Current length of a String*/

	if(mkdir(chPWD,ACCESSPERMS) == -1)											/*	Make a direcory with name specified in chPWd string*/
		perror("Error making directory");

	iSockfd = socket(AF_INET, SOCK_STREAM, 0);									/*	Create a socket*/


	Client_Address.sin_family = AF_INET;										/*	Socket family*/
	Client_Address.sin_addr.s_addr = inet_addr("127.0.0.1");					/*	Loop back IP*/
	Client_Address.sin_port = htons(9734);										/*	Server port*/
	iLen = sizeof(Client_Address);												/*	Length of client address*/

	iResult = connect(iSockfd, (struct sockaddr *)&Client_Address, iLen);		/*	Connect to the server*/
	if(iResult == -1)
	{
		perror("Error in connecting to the server.\n"							/*	Error message*/
				"This will terminate the program.\n");
		close(iSockfd);															/*	Close the created socket*/
		exit(EXIT_FAILURE);														/*	Exit with failure*/
	}

	while(1)
	{
		Print_Info();															/*	Prints the basic info*/
		if(strncmp(chOption_Buffer,"1\n",2) == 0 ||								/*	Check for the user input*/
				strncmp(chOption_Buffer,"2\n",2) == 0 )
		{
			sleep(3);															/*	Sleep for 3 seconds*/
			write(iSockfd,chOption_Buffer,sizeof(chOption_Buffer));				/*	Send the scanned user option to server*/

			read(iSockfd,chBuffer,sizeof(chBuffer));							/*	Read the server response*/
			memset(chBuffer,0x00,sizeof(chBuffer));								/*	Clean the buffer*/

			read(iSockfd,chBuffer,sizeof(chBuffer));							/*	Read the server response*/
			printf("Message from the server is\n%s\n",chBuffer);				/*	Prints the message in Client's environment*/
			memset(chBuffer,0x00,sizeof(chBuffer));
		}
		else if(strncmp(chOption_Buffer,"4\n",2) == 0 )							/*	Check for the user input*/
		{
			write(iSockfd,chOption_Buffer,sizeof(chOption_Buffer));				/*	Send the user selected option to the client*/
			printf("Quiting\n");												/*	Print the information*/
			break;																/*	Break the loop*/
		}
		else if(strncmp(chOption_Buffer,"3\n",2) == 0 )							/*	Check for the user input*/
		{
			write(iSockfd,chOption_Buffer,sizeof(chOption_Buffer));				/*	Send to the server*/
			printf("Please give a file name from the list above\n"				/*	Scan the user iput for file name to be downloaded*/
					"Which file to download?:");
			fgets(chBuffer,sizeof(chBuffer),stdin);								/*	Read in the file name*/

			memset(chFile_Path+iStr_Len,0x00,sizeof(chFile_Path)-iStr_Len);		/*	Clean the bytes except the values stored in*/
			strncpy(chFile_Path+iStr_Len,chBuffer,strlen(chBuffer)-1);			/*	Copy the File name in path string*/
			printf("%s\n",chFile_Path);											/*	Print the Full path*/

			write(iSockfd,chBuffer,sizeof(chBuffer));							/*	Send the file name to server*/
			memset(chBuffer,0x00,sizeof(chBuffer));

			fptrDownloads = fopen(chFile_Path,"w");								/*	Open a file for writing server data*/

			read(iSockfd,chBuffer,sizeof(chBuffer));							/*	Read the server response*/
			iLen = atoi(chBuffer);												/*	Convert the server response into integer as server has sent
			 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	us the file length*/

			chptrTemp_Buf = (char *)malloc(iLen*sizeof(char));					/*	Allocate a memory with server specified file length*/
			if(chptrTemp_Buf == NULL)
				perror("Not enough space\n");									/*	Error message*/

			memset(chptrTemp_Buf,0x00,iLen);									/*	Clean the buffer*/

			iRead = read(iSockfd,chptrTemp_Buf,iLen);							/*	Read the file server has sent us*/
			if(iRead != iLen)
			{
				fprintf(stderr,"Actual size of file is %d byes\n"				/*	Error in reading*/
						"Downloaded size is %d bytes \n",iLen,iRead);
				perror("Error Reading a file\n");								/*	Error message with specified error*/
				if(close(iSockfd) == -1)										/*	Close the connection*/
				{
					perror("Error in closing socket\n");						/*	Error message*/
					break;
				}
				break;															/*	Break the loop*/
			}
			printf("Message from the server is\n%s\n",chptrTemp_Buf);			/*	Print the server message*/

			iRead = fwrite(chptrTemp_Buf,sizeof(char),iLen,fptrDownloads);		/*	Write the to the opened file*/
			if(iRead != iLen)
				perror("Error downloading a file.\n");							/*	Error in writing data*/

			free(chptrTemp_Buf);												/*	Free up the memory allocated earlier*/
			sleep(5);
			fclose(fptrDownloads);												/*	Close the file opened earlier*/
		}
	}
	if(close(iSockfd) == -1)													/*	Close the socket*/
		perror("Error in closing socket\n");									/*	Error in closing*/
	return 0;
}


void Print_Info(void)
{
	printf("1. File_List.txt\n"													/*	Take an input from user*/
			"2. File_Info.txt\n"
			"3. Download a file?\n"
			"4. Quit\n");
	printf("Enter an option: ");
	fgets(chOption_Buffer,sizeof(chOption_Buffer),stdin);
}
