/**
 * @file Chat_Chat.c
 * @author Tejas prajapati
 * @date 13-08-15
 * @brief File containing Program of TCP Client of Chat application
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include 	<sys/types.h>


typedef struct sockaddr_in 	Socket_t;											/**<Structure is renamed for shorter name in program*/
typedef struct timeval		Time_Out_t;											/**<Structure is renamed for shorter name in program*/

void 		Get_User_Name(char *);												/**<Get the user name of the pc*/


/*
 * @brief Client Program starts from here.
 * @param [IN] None
 * 		  [OUT] 0 on success and 1 on failure
 *
 * This is the main function of the client program. This function
 * declare the variables and set them to the initial condition.
 *
 * This function calls the supporting functions to perform the
 * task of the server. Functions that are called in this function
 * are like Get_User_Name() thisfunctions are user defined
 * functions other functions like fsync(), select(), accept()
 * are also called in this functionto perform the requirement
 * of the server.
 *
 * This function prints the user info on the screen as well as
 * messages that are passed from the server if any.
 */
int main()
{
	char		chUser_Name[33];												/**<User name*/
	char		chBuffer[100];													/**<Buffer for reading message*/
	char		chServer_Ip[20];												/**<Server's IP address*/
	char		chPort_Num[7];													/**<Port number array*/
	char		chMsg[100];														/**<Msg buffer*/
	int			iMsg_Len;														/**<Msg length of the msg to be pass to the server*/
	int			iSockfd;														/**<Socket fd*/
	int			iLen;															/**<Length of the socket*/
	int			iResult;														/**<Result of any function*/
	int			iPort_Num;														/**<Port number which will be passed in Socket connection*/
	Socket_t 	Client_Address;													/**<Client adderss socket*/
	Time_Out_t	Read_Time_Out,Scan_Input;										/**<Time out struct object*/
	fd_set		Read_fds,Terminal_Fds;											/**<File descriptor set*/

	memset(chBuffer,0x00,sizeof(chBuffer));										/**<Clean the buffer*/
	memset(chMsg,0x00,sizeof(chMsg));											/**<Clean the buffer*/

	Get_User_Name(chUser_Name);													/**<Get the user name*/
	
	strncpy(chBuffer,chUser_Name,strlen(chUser_Name)-1);						/**<Copy the user name for further msg transfers*/
	strcat(chBuffer,": ");
	iMsg_Len = strlen(chBuffer);												/**<Length of the message to be passed normally*/

	iSockfd = socket(AF_INET, SOCK_STREAM, 0);									/**<Create a socket*/
	if(iSockfd == -1)
	{
		perror("Error creating socket");										/**<Error message*/
		exit(EXIT_FAILURE);
	}

	printf("Please provide the Server's IP address: ");							/**<Information for the user*/
	fgets(chServer_Ip,20,stdin);												/**<Get the required information from the user*/
	fsync(0);																	/**<Sync the output of stdin*/

	printf("Please provide the Port Number: ");									/**<Information for the user*/
	fgets(chPort_Num,7,stdin);													/**<Get the required information from the user*/
	fsync(0);																	/**<Sync the output of stdin*/

	strtok(chServer_Ip,"\n");													/**<Eliminate the last \n character*/
	strtok(chPort_Num,"\n");													/**<Eliminate the last \n character*/

	iPort_Num = atoi(chPort_Num);												/**<Converts a string to an integer*/

	Client_Address.sin_family = AF_INET;										/**<Socket family*/
	Client_Address.sin_addr.s_addr = inet_addr(chServer_Ip);					/**<Loop back IP*///inet_addr("127.0.0.1")
	Client_Address.sin_port = htons(iPort_Num);									/**<Server port*/
	iLen = sizeof(Client_Address);												/**<Length of client address*/

	iResult = connect(iSockfd, (struct sockaddr *)&Client_Address, iLen);		/**<Connect to the server*/
	if(iResult == -1)
	{
		perror("Error in connecting to the server.\n"							/**<Error message*/
				"If server is not running please first run the server.\n"
				"This will terminate the program.\n");
		close(iSockfd);															/**<Close the created socket*/
		exit(EXIT_FAILURE);														/**<Exit with failure*/
	}

	write(iSockfd,chUser_Name,strlen(chUser_Name)-1);							/**<Write user name to the server*/
	fsync(iSockfd);																/**<Sync with the server*/

	printf("Type the message you want to send or \"exit\" to quit\n");

	while(1)
	{
		FD_ZERO(&Terminal_Fds);													/**<Clean the file descriptor*/
		FD_SET(0,&Terminal_Fds);												/**<Set the stdin into the wait list*/

		Scan_Input.tv_sec = 1;													/**<Set the timer to 1 sec*/
		Scan_Input.tv_usec = 500000;											/**<Add .5 sec to the timer*/

		iResult = select(1,&Terminal_Fds,NULL,NULL,&Scan_Input);				/**<Set and start the timer*/
		if(iResult == -1)
			perror("Error in select()");										/**<Error setting a timer*/
		else if(iResult)
		{
			memset(chMsg,0x00,sizeof(chMsg));									/**<Clean the reading buffer*/
			read(0,chMsg,90);													/**<Read the data from the stdin*/
			memset(chBuffer+iMsg_Len,0x00,sizeof(chBuffer)-iMsg_Len);			/**<Keeping the user name and cleaning the rest*/
			strcpy(chBuffer+iMsg_Len,chMsg);									/**<Copy the message to the sending buffer*/
			write(iSockfd,chBuffer,strlen(chBuffer));							/**<Write data to the server*/
			fsync(iSockfd);														/**<Sync with the server*/

			if(strstr(chMsg,"exit\n") != NULL)									/**<If exit is received*/
				break;															/**<Break the loop*/

			memset(chMsg,0x00,sizeof(chMsg));									/**<Clean the message buffer*/
		}

		FD_ZERO(&Read_fds);														/**<Clean the file descriptor*/
		FD_SET(iSockfd,&Read_fds);												/**<Set the socket to the List*/

		Read_Time_Out.tv_sec = 1;												/**<Set the timeout timer to 1 sec*/
		Read_Time_Out.tv_usec = 500000;											/**<Add .5 sec in timer*/

		iResult = select(iSockfd+1,&Read_fds,NULL,NULL,&Read_Time_Out);			/**<Set and start the timer*/
		if(iResult == -1)
			perror("Error in select()");										/**<Error message*/
		else if(iResult)
		{
			memset(chMsg,0x00,sizeof(chMsg));									/**<Clean the message buffer*/
			read(iSockfd,chMsg,sizeof(chMsg));									/**<Read the data from the server*/
			printf("%s",chMsg);													/**<Print on the screen*/
		}
	}

	if(shutdown(iSockfd,2) == -1)												/**<Stops both reception and transmission of data*/
		perror("Error in shutdown()");											/**<Error message*/

	if(close(iSockfd) == -1)													/**<Close the socket*/
		perror("Error closing a socket in client");								/**<Error*/

	return 0;
}


/*
 * @brief	Get the user name from the pc directly
 * @param	char * that points to the passed array of characters
 * @retval	None
 *
 * This function get the user name from the linux command
 * "whoami" to get the output in the buffer this function
 * uses the basic pipe commands to perform the above
 * mentioned task.
 */
void Get_User_Name(char *chTemp)
{
	FILE	*fptrRead_User_Name;												/**<File pointer to open a pipe*/
	int		iLocal;																/**<Local variable*/

	fptrRead_User_Name = popen("whoami","r");									/**<Opens a pipe for reading*/
	if(fptrRead_User_Name != NULL)
	{
		iLocal = fread(chTemp,sizeof(char),100,fptrRead_User_Name);				/**<Read the pipe*/
		if(iLocal == 0)
			perror("Error in reading opened pipe\n");							/**<Error message*/
	}
	if(pclose(fptrRead_User_Name) == -1)										/**<Close the pipe after reading is done*/
	{
		perror("Error in closing the opened pipe.\n"							/**<Error message*/
				"This will terminate the program.\n");
		exit(EXIT_FAILURE);														/**<Program should not continue as it will not perform																					as it should be*/
	}
}
