/*
 * FPT_Functios.c
 *
 *  Created on: 10-Aug-2015
 *      Author: tejas
 */

#include	"FTP_Functions.h"


extern char		chStore_File_Path[2][70];										/*	Path to store the file information*/
extern FILE		*fptrFiles;														/*	Access the File_List.txt*/
extern FILE		*fptrFile_Info;													/*	Access the File_Info.txt*/
extern int 		iStore;															/*	Determines how many files to read MAX 20 can be read*/
extern char 	chFiles[20][70];												/*	List of files scanned from directory is stored in this*/
extern char		chFull_Path[150];												/*	Path to scan/ open the directory*/
extern int		iStr_Len;														/*	Checks for the length of the chFull_Path*/
extern int		iServer_Sockfd;
Socket_t 		Server_Socket;


/*
 * Function name	:	Create_List_Of_Files
 *
 * Description		:	use this function to Create a file list and info list
 * 						in a text file. This files will be created on the
 * 						desktop. File names are File_List.txt and File_Info.txt
 * 						Please do not delete this file from the desktop
 * 						this will be used till the program ends
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Create_List_Of_Files(void)
{
	struct 	stat 	Status_of_File;												/*	Structure for scanning files information*/
	int 			iLength;													/*	Get the file name length*/
	char 			chDate[30];													/*	Convert the raw information to Readable date and time*/
	float 			fSize;														/*	Size of the file*/
	int				iLocal;														/*	Local variable*/

	strcat(chStore_File_Path[0],"/Desktop/File_Info.txt");						/*	File path to open*/
	fptrFile_Info = fopen(chStore_File_Path[0],"w+");							/*	Open a file*/
	if(fptrFile_Info == NULL)
	{
		perror("Error in creating file info list.\n"							/*	Error message*/
				"This will terminate the program");
		exit(EXIT_FAILURE);														/*	Program should terminate otherwise results may be worse*/
	}

	strcat(chStore_File_Path[1],"/Desktop/File_List.txt");						/*	File path to open*/
	fptrFiles = fopen(chStore_File_Path[1],"w+");								/*	Open a file*/
	if(fptrFiles == NULL)
	{
		perror("Error in creating file list.\n"									/*	Error message*/
				"This will terminate the program");
		exit(EXIT_FAILURE);														/*	Program should terminate otherwise results may be worse*/
	}


	for(iLocal=0;iLocal<iStore;iLocal++)
	{
		fprintf(fptrFiles,"%d. %s",iLocal+1,chFiles[iLocal]);					/*	Write the data to the file*/

		iLength = strlen(chFiles[iLocal]);										/*	Delete a \n character form the file name*/
		chFiles[iLocal][iLength-1] = '\0';

		strcpy(chFull_Path+iStr_Len, chFiles[iLocal]);							/*	Convert a file name to its full path*/

		if (stat(chFull_Path, &Status_of_File))									/*	Get the file details*/
			perror(chFiles[iLocal]);											/*	Error message*/
		else
		{
			fSize = (float)Status_of_File.st_size;								/*	Convert a file size in KB*/
			fSize /= (1000);
			strftime(chDate, 21, "%d-%m-%y %r"									/*	Convert a raw data in readable format*/
					, localtime(&(Status_of_File.st_mtime)));
			fprintf(fptrFile_Info,"%d.%s is Last Modified on: %s "				/*	Print the data in opened file*/
								  ", File size is: %.1f KB\n\n",
								  iLocal+1,
								  chFiles[iLocal],
								  chDate, fSize);
		}
	}
}


/*
 * Function name	:	Get_User_Name
 *
 * Description		:	use this function to Scan the user name and set the scanning
 * 						path for files to downloads of the particular user.
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Get_User_Name(void)
{
	int			iLocal;
	char		chTemp[100];													/*	Temp variable to store the pipe information*/
	int			iSuccess;														/*	Directory scanning is successful or not*/
	FILE		*fptrRead_User_Name;											/*	Reads the username by pipe*/


	fptrRead_User_Name = popen("whoami","r");									/*	Opens a pipe for reading*/
	if(fptrRead_User_Name != NULL)
	{
		iLocal = fread(chTemp,sizeof(char),100,fptrRead_User_Name);				/*	Read the pipe*/
		if(iLocal == 0)
			perror("Error in reading opened pipe\n");							/*	Error message*/
	}
	if(pclose(fptrRead_User_Name) == -1)										/*	Close the pipe after reading is done*/
	{
		perror("Error in closing the opened pipe.\n"							/*	Error message*/
				"This will terminate the program.\n");
		exit(EXIT_FAILURE);														/*	Program should not continue as it will not perform
																					as it should be*/
	}


	strcpy(chFull_Path,"/home/");												/*	String formation for Static directory scanning*/
	strncat(chFull_Path,chTemp,strlen(chTemp)-1);								/*	Add the user name*/
	strcpy(chStore_File_Path[0],chFull_Path);									/*	Files to be stored path*/
	strcpy(chStore_File_Path[1],chFull_Path);									/*	Files to be stored path*/
	strcat(chFull_Path,"/Downloads/");											/*	Path to scan*/

	iStr_Len = strlen(chFull_Path);												/*	String length of path*/

	iSuccess = Get_Dir(chFull_Path,0);											/*	Checks if directory scanning is successful or not*/
	if(iSuccess == 0)
	{
		printf("Please provide a directory for scan\n");						/*	Error message*/
	}

}


/*
 * Function name	:	Connect_Socket_Server
 *
 * Description		:	use this function to Create and connect a socket server
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Connect_Socket_Server(void)
{
	int 		iServer_Len;													/*	Length of server socket*/

	iServer_Sockfd = socket(AF_INET, SOCK_STREAM, 0);							/*	Creates a socket for server*/
	if(iServer_Sockfd == -1)
	{
		fprintf(stderr,"Socket creation failed in server. "						/*	Error in creating a socket*/
				"Program will terminate.\n");
		exit(EXIT_FAILURE);														/*	Exit the program as no other function can work*/
	}


	Server_Socket.sin_family = AF_INET;											/*	Setting values in structure*/
	Server_Socket.sin_addr.s_addr = htonl(INADDR_ANY);							/*	Accepts any IP*/
	Server_Socket.sin_port = htons(9734);										/*	Accepts connection on this port*/
	iServer_Len = sizeof(Server_Socket);

	bind(iServer_Sockfd, (struct sockaddr *)&Server_Socket, iServer_Len);		/*	Bind the socket_fd to Server_Socker*/

	listen(iServer_Sockfd, 5);													/*	Listen the clients maximum of 5*/
}


