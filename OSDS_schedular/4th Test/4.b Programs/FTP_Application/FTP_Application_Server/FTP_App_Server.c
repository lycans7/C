/*
 * Server_Multi_Client.c
 *
 *  Created on: 10-Aug-2015
 *      Author: tejas
 */

#include	"FTP_Functions.h"




int 		iStore;																/*	Determines how many files to read MAX 20 can be read*/
char 		chFiles[20][70];													/*	List of files scanned from directory is stored in this*/
char 		chFull_Path[150];													/*	Path to scan/ open the directory*/
char		chStore_File_Path[2][70];											/*	Path to store the file information*/
FILE		*fptrFile_Info;														/*	Access the File_Info.txt*/
FILE		*fptrFiles;															/*	Access the File_List.txt*/
int			iStr_Len;															/*	Checks for the length of the chFull_Path*/
char		chOption[15];														/*	Checks the options selected by client*/
int			iClient_Sockfd;														/*	File descriptor of client socket*/
int			iServer_Sockfd;														/*	File descriptor of server socket*/
Socket_t 	Client_Socket;														/*	Client and Server socket structures*/
pid_t		Child_Process;														/*	Child process variable of type pid_t*/



void 	Option_1_Response(void);												/*	Function which responde to the client's slection*/
void 	Option_2_Response(void);												/*	Function which responde to the client's slection*/
void 	Option_3_Response(void);												/*	Function which responde to the client's slection*/
void	Close_All(void);														/*	Close all the open File descriptor*/



int main()
{
	int		iClient_Len;														/*	Length of client socket*/
	int		iNum_Connections = 0;												/*	Number of connections established*/
	int		iBreak_Time = 0;													/*	Check if the client has withdrawn the connection or not*/
	int		iMsg_ID;															/*	Message queue file descriptor*/

	memset(chOption,0x00,sizeof(chOption));										/*	Cleaning the option buffer*/

	printf("In this program TCP sockets are used as in TCP,\n"
			"it is possible to set time out for connected  sockets and\n"
			"multiple clients can get connected.\n"
			"Press any key to continue...\n");
	getchar();

	Get_User_Name();															/*	Get the user name from the Pipe*/

	Create_List_Of_Files();														/*	Creates a list of files*/

	Connect_Socket_Server();													/*	Create and connect to the server socket*/

	printf("Server is waiting\n");

	while(1)
	{
		int			iRet_Val;													/*	Return value from select() is stored in this*/
		long int	liMsg_Type = 0;												/*	Message queue message type*/
		Time_Out_t	Connection_Accept_Time;										/*	Time out struct object for accepting connection*/
		fd_set		Accept_Fds;													/*	File descriptor of the above mentioned timeout*/


		if(iBreak_Time == 1)													/*	If this variable is set*/
		{
			msgrcv(iMsg_ID,														/*	Receive a msg from the client for disconnection*/
				   (void *)&Parent_Child_t,
				   100,
				   liMsg_Type, IPC_NOWAIT);
			if(strcmp(Parent_Child_t.chNum_Connection,							/*	Check what is the received msg*/
					"Client is disconnecting\n") == 0)
			{
				memset(Parent_Child_t.chNum_Connection,0x00,100);				/*	Clean the msg so that it doesnt come again unneccesarly*/
				printf("%s",Parent_Child_t.chNum_Connection);					/*	Print the message passed by the child client*/
				iNum_Connections--;												/*	Decrease the number of connection*/
			}
			printf("Num of Connections:%d\n",iNum_Connections);
			if(iNum_Connections == 0)											/*	If number of connection is found to be 0 then terminate the program*/
				break;
			printf("Server is waiting\n");
		}

		Connection_Accept_Time.tv_sec = 3;										/*	Time out value of 3 seconds*/
		Connection_Accept_Time.tv_usec = 0;										/*	Time out value of 3 seconds and 0 micro-seconds*/

		FD_ZERO(&Accept_Fds);													/*	Clean the file descriptor*/
		FD_SET(iServer_Sockfd, &Accept_Fds);									/*	Set the sever "who accepts the connection" to the file descriptors*/

		iRet_Val = select(100,&Accept_Fds,NULL,NULL,&Connection_Accept_Time);	/*	Set a value specified in above time out struct*/
		if(iRet_Val == -1)														/*	Error if return value is -1*/
			perror("Read time out selection occurred an error");				/*	Error msg*/
		else if(iRet_Val)
		{
			iClient_Len = sizeof(Client_Socket);								/*	Client socket size*/
			iClient_Sockfd = accept(iServer_Sockfd,								/*	Accepts the connection from a client*/
									(struct sockaddr *)&Client_Socket,
									(socklen_t *)&iClient_Len);
			printf("iClient_Sockfd: %d\n",iClient_Sockfd);						/*	Print the information regarding the connection established*/
			iBreak_Time = 1;													/*	Set the variable so that it will next time check whether to break or not*/
			iNum_Connections++;													/*	Increament the connection*/
		}
		else
			continue;															/*	Continue from the while 1 if no connection request for 3 seconds*/


		iMsg_ID = msgget((key_t)1234, 0666 | IPC_CREAT);						/*	Create a message queue*/
		if (iMsg_ID == -1)
		{
			fprintf(stderr, "msgget failed with error: %d\n", errno);			/*	Error msg*/
			exit(EXIT_FAILURE);
		}

		Child_Process = fork();													/*	Create a child*/
		if(Child_Process == -1)
		{
			perror("Can not create child process");								/*	Error msg*/
		}
		else if(Child_Process == 0)
		{
			fd_set 		Client_Fds;												/*	Client file descriptor*/
			Time_Out_t 	Client_Time_Out;										/*	Time out for client*/
			int 		iRetval;												/*	Return value from the select*/


			if(close(iServer_Sockfd) == -1)										/*	Close the duplicate file descriptor*/
				perror("Child can not proceed");								/*	Error msg*/

			FD_ZERO(&Client_Fds);												/*	Clean the file descriptors*/
			FD_SET(iClient_Sockfd, &Client_Fds);								/*	Set the client socket in time out structure*/

			Client_Time_Out.tv_sec = 120;										/*	Set the time to 120 Seconds*/
			Client_Time_Out.tv_usec = 0;										/*	Set the time to 0 micro-seconds*/
			while(1)
			{
				iRetval = select(100, &Client_Fds,								/*	Set the client with 120 second time out*/
								 NULL, NULL,
								 &Client_Time_Out);

				printf("Time remaining for client %d is : %0.0f\n"				/*	Prints the remianing time for a particular client*/
						,iClient_Sockfd,(float)Client_Time_Out.tv_sec);

				if (iRetval == -1)
					perror("select()");											/*	Error in select function*/
				else if (iRetval)
				{
					read(iClient_Sockfd, chOption, sizeof(chOption));			/*	Read data from client for options*/
					printf("%s\n",chOption);									/*	Print which option client has selected*/
					Option_1_Response();										/*	Responde accordingly to chOption buffer*/
					Option_2_Response();										/*	Responde accordingly to chOption buffer*/
					Option_3_Response();										/*	Responde accordingly to chOption buffer*/
					if(strncmp(chOption,"4\n",2) == 0)							/*	Responde accordingly to chOption buffer*/
					{
						memset(chOption,0x00,sizeof(chOption));
						printf("\nQuiting\n");
						break;													/*	Break the loop*/
					}

					Client_Time_Out.tv_sec = 120;								/*	Set the value back to 120 seconds as client has responded
					 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	in time*/
					Client_Time_Out.tv_usec = 0;								/*	Same as above*/
				}
				else
				{
					printf("No data within 120 seconds.\n");					/*	Information*/
					break;														/*	Break the connection if no data for 120 seconds*/
				}
			}

			strcpy(Parent_Child_t.chNum_Connection								/*	Copy the data in to Message queue structure*/
					,"Client is disconnecting\n");
			Parent_Child_t.liMsg_Type = 1;										/*	Message is to be send*/

			printf("%s",Parent_Child_t.chNum_Connection);						/*	Print the message*/

			if (msgsnd(iMsg_ID, (void *)&Parent_Child_t, 100, 0) == -1)			/*	Send the message*/
			{
				fprintf(stderr, "msgsnd failed\n");								/*	Error msg*/
				exit(EXIT_FAILURE);
			}

			Close_All();														/*	Close all related open descriptors*/
			printf("Child Terminated...\n");									/*	Child is terminated*/
			exit(EXIT_SUCCESS);													/*	Exit with success*/
		}
	}
	Close_All();																/*	Close all related open descriptors with Parent process*/
	if (msgctl(iMsg_ID, IPC_RMID, 0) == -1)										/*	Remove the message queue*/
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");							/*	Error msg*/
		exit(EXIT_FAILURE);
	}

	printf("Server Terminated...\n");											/*	Information*/
	return 0;
}





/*
 * Function name	:	Option_1_Response
 *
 * Description		:	use this function to Responde the client if the the option 1
 * 						was chosen by client
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Option_1_Response(void)
{
	char	*chptrTemp_Buf = NULL;												/*	Temporary storage buffer*/
	int		iNum_To_Read;														/*	Number of bytes to be read*/

	if(strncmp(chOption,"1\n",2) == 0)											/*	Check if the correct option for the function*/
	{
		memset(chOption,0x00,sizeof(chOption));
		iNum_To_Read = ftell(fptrFiles);										/*	Stores the number of bytes to be read into variable*/
		if(fseek(fptrFiles, 0L, SEEK_SET) == -1)								/*	Rewind the file pointer*/
			perror("Error in rewinding the file to read\n");					/*	Error message*/

		sprintf(chOption,"%d",iNum_To_Read);									/*	Convert the read value in string*/
		sleep(1);																/*	Sleep for 1 second*/
		write(iClient_Sockfd,chOption,strlen(chOption));						/*	Send the information to the client*/
		memset(chOption,0x00,sizeof(chOption));

		chptrTemp_Buf = (char *)malloc(iNum_To_Read*sizeof(char));				/*	Allocate a memory of bytes needed to be read*/
		if(chptrTemp_Buf == NULL)												/*	Error acquring the memory*/
			perror("Error in allocating memory\n");

		fread(chptrTemp_Buf,sizeof(char),iNum_To_Read,fptrFiles);				/*	Display the files as it is*/
		sleep(3);																/*	Sleep for 3 seconds*/
		write(iClient_Sockfd,chptrTemp_Buf,iNum_To_Read);						/*	Send file to the client*/
		free(chptrTemp_Buf);													/*	Free up the buffer allocated earlier*/
	}
}



/*
 * Function name	:	Option_2_Response
 *
 * Description		:	use this function to Responde the client if the the option 2
 * 						was chosen by client
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Option_2_Response(void)
{
	char	*chptrTemp_Buf = NULL;												/*	Temporary storage buffer*/
	int		iNum_To_Read;														/*	Number of bytes to be read*/

	if(strncmp(chOption,"2\n",2) == 0)											/*	Check if the correct option for the function*/
	{
		memset(chOption,0x00,sizeof(chOption));
		iNum_To_Read = ftell(fptrFile_Info);									/*	Stores the number of bytes to be read into variable*/
		if(fseek(fptrFile_Info, 0L, SEEK_SET) == -1)							/*	Rewind the file pointer*/
			perror("Error in rewinding the file to read\n");					/*	Error Message*/

		sprintf(chOption,"%d",iNum_To_Read);									/*	Convert the read value in string*/
		sleep(1);
		write(iClient_Sockfd,chOption,strlen(chOption));						/*	Send the information to the client*/
		memset(chOption,0x00,sizeof(chOption));									/*	Clean the option buffer*/

		chptrTemp_Buf = (char *)malloc(iNum_To_Read*sizeof(char));				/*	Allocate a memory of bytes needed to be read*/
		if(chptrTemp_Buf == NULL)												/*	Error acquring the memory*/
			perror("Error in allocating memory\n");

		fread(chptrTemp_Buf,sizeof(char),iNum_To_Read,fptrFile_Info);			/*	Display the files as it is*/
		sleep(3);
		write(iClient_Sockfd,chptrTemp_Buf,iNum_To_Read);						/*	Send file to the client*/
		free(chptrTemp_Buf);													/*	Free up the buffer allocated earlier*/
	}
}



/*
 * Function name	:	Option_3_Response
 *
 * Description		:	use this function to Responde the client if the the option 3
 * 						was chosen by client. This function reads the file to transfer
 * 						to client and send it afterwards.
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Option_3_Response(void)
{
	int 	iLocal;																/*	Local variable*/
	int 	iLength;															/*	Get the file name length*/
	int		iNum_To_Read;														/*	Number of bytes to be read*/
	FILE	*fptrSend = NULL;													/*	File pointer for the file to open which is requested by client*/
	char	*chptrTemp_Buf = NULL;												/*	Temporary storage buffer*/
	char	chBuffer[2048];														/*	Buffer*/

	memset(chBuffer,0x00,sizeof(chBuffer));

	if(strncmp(chOption,"3\n",2) == 0)											/*	Check if the correct option for the function*/
	{
		memset(chOption,0x00,sizeof(chOption));
		memset(chBuffer,0x00,sizeof(chBuffer));

		read(iClient_Sockfd, chBuffer, sizeof(chBuffer));						/*	Read the file name from the client*/
		iLength = strlen(chBuffer);												/*	Modify the received file name*/
		chBuffer[iLength -1] = '\0';											/*	Remove the trailing '\n' character*/

		for(iLocal = 0; iLocal < iStore ;iLocal++)								/*	Scan which file is requested*/
			if(strcmp(chBuffer,chFiles[iLocal]) == 0)							/*	Compare the file name*/
				break;															/*	If found break the loop*/
		strcpy(chFull_Path+iStr_Len, chFiles[iLocal]);							/*	Convert a file name to its full path*/

		fptrSend = fopen(chFull_Path,"r");										/*	Open the file with read type*/

		fseek(fptrSend, 0L, SEEK_END);											/*	Seek to the end*/
		iNum_To_Read = ftell(fptrSend);											/*	So that how many bytes needed to be read is found*/
		if(fseek(fptrSend, 0L, SEEK_SET) == -1)									/*	Rewind the file pointer*/
			perror("Error in rewinding the file to read\n");					/*	Error Message*/

		sleep(1);
		sprintf(chOption,"%d",iNum_To_Read);									/*	Convert the byte counts in string*/
		write(iClient_Sockfd,chOption,strlen(chOption));						/*	Send it to the client*/
		memset(chOption,0x00, sizeof(chOption));

		chptrTemp_Buf = (char *)malloc(iNum_To_Read*sizeof(char));				/*	Allocate buffer a memory*/
		if(chptrTemp_Buf == NULL)												/*	Error msg*/
			perror("Error in allocating memory\n");

		fread(chptrTemp_Buf,sizeof(char),iNum_To_Read,fptrSend);				/*	Display the files as it is*/
		sleep(3);
		write(iClient_Sockfd,chptrTemp_Buf,iNum_To_Read);						/*	Send the file to the client*/

		free(chptrTemp_Buf);													/*	Free the allocated buffer*/
		fclose(fptrSend);														/*	Close the opened file*/
	}
}



/*
 * Function name	:	Close_All
 *
 * Description		:	use this function to Close all the open file descriptor
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Close_All(void)
{
	if(Child_Process == 0)														/*	If you are in child process close the client socket*/
		if(close(iClient_Sockfd) == -1)											/*	Error in closing the client socket*/
			perror("Error closing the socket");

	if(Child_Process > 0)														/*	If you are in parent process*/
		if(close(iServer_Sockfd) == -1)											/*	Close the Server socket*/
			perror("Error closing the socket");

	if(fclose(fptrFile_Info) != 0)												/*	Close the file opened earlier*/
		perror("Error in closing file info list\n");							/*	Error message*/

	if(fclose(fptrFiles) != 0)													/*	Close the file opened earlier*/
		perror("Error in closing file list\n");									/*	Error message*/
}
