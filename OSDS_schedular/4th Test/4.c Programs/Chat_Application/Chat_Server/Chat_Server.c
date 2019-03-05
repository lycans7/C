/**
 * @file Chat_server.c
 * @author Tejas prajapati
 * @date 13-08-15
 * @brief File containing Program of TCP Server of Chat application
 */


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<mqueue.h>
#include	<netinet/in.h>
#include	<sys/socket.h>
#include 	<sys/msg.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<errno.h>


/*
 * @brief Structures are renamed for shorter and convinient name
 *
 * sockaddr_in is the structure for connecting the server and
 * clients which we have given a shorter name for better useability
 * in code.
 *
 * timeval is the structure for making a time out on the selected fds
 * which to we have given a meaning full name
 */
typedef struct sockaddr_in 	Socket_t;											/**<Structure is renamed for shorter name in program*/
typedef struct timeval		Time_Out_t;											/**<Structure is renamed for shorter name in program*/

/*
 * @brief Structure for Listing the connected users to the server
 *
 * List is the structure that will be having a user name of the
 * connected client and the socket file descriptor for the particular
 * client user. We have renamed it because we don't want to use the
 * name of the structure following a struct keyword.
 */
typedef struct List
{
	char	chConnected_User[35];												/**<User name on the client pc*/
	int		iSocket_Number;														/**<Socket fd by which user is connected*/
}List_Of_Users_t;

Socket_t 	Server_Address;														/**<Server socket structure*/
int			iServer_Sockfd;														/**<File descriptor of server socket*/
pid_t		Child_Process;														/**<Child process variable of type pid_t*/


void 		Get_User_Name(char *);												/**<Get the user name Function decleration*/
void		Connect_Socket_Server(void);										/**<Create a socket on which users can connect Function decleration*/


/*
 * @brief Server Program starts from here.
 * @param [IN] None
 * 		  [OUT] 0 on success and 1 on failure
 *
 * This is the main function of the server program. This function
 * declare the variables and set them to the initial condition.
 *
 * This function calls the supporting functions to perform the
 * task of the server. Functions that are called in this function
 * are like Get_User_Name() and Connect_Socket_server() this
 * functions are user defined functions other functions like
 * fsync(), select(), accept() are also called in this function
 * to perform the requirement of the server.
 *
 * This function prints the user info on the screen as well as
 * messages that are passed from the client.
 *
 * This function as is the only main function creates a child
 * process for each and every connected client. This child
 * process will take the charge of printing client's messages to
 * the terminal.
 */
int main()
{
	char 			chUser_Name[33];											/**<User name variable*/
	char			chMessage[100];												/**<Message read in from client*/
	char			chQueue_Msg[BUFSIZ];										/**<Message queue buffer*/
	char			chClient_User[35];											/**<Client's user name is read in*/
	char			chRead_Buf[100];											/**<Message reading buffer*/
	int				iMsg_Len;													/**<Length of the message containing user name*/
	int				iNum_Connections = 0;										/**<Number of live connection*/
	int				iBreak_Time = 0;											/**<For skipping the logic 1st time*/
	Socket_t		Client_Socket;												/**<Client socket structure*/
	Time_Out_t		Connection_Accept_Time,Scan_Input;							/**<Time out struct object for accepting connection an
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	Reading data from Terminal*/
	fd_set			Accept_Fds, Terminal_Fds;									/**<File descriptor of the above mentioned timeout*/
	mqd_t			Message_Queue;												/**<Message queue object*/
	List_Of_Users_t	List_Users[5];												/**<Number of clients connected to it*/
	int				iRet_Val;													/**<Return value from select() is stored in this*/
	int				iClient_Sockfd;												/**<File descriptor of client socket*/
	int				iClient_Len;												/**<Length of client socket*/
	int 			iLocal;														/**<Local variable*/


	memset(chUser_Name,0x00,sizeof(chUser_Name));								/**<Cleaning the Buffer*/
	memset(chQueue_Msg,0x00,sizeof(chQueue_Msg));								/**<Cleaning the Buffer*/
	memset(chMessage,0x00,sizeof(chMessage));									/**<Cleaning the Buffer*/
	memset(chClient_User,0x00,sizeof(chClient_User));							/**<Cleaning the Buffer*/
	memset(chRead_Buf,0x00,sizeof(chRead_Buf));									/**<Clean the Read buffer*/

	Get_User_Name(chUser_Name);													/**<Get the user name from the PC running the program*/

	strncpy(chMessage,chUser_Name,strlen(chUser_Name)-1);						/**<Copy user name into msg to be passed to the client*/
	strcat(chMessage,": ");
	iMsg_Len = strlen(chMessage);												/**<Measuring the length*/

	Connect_Socket_Server();													/**<Create a socket*/

	printf("Server is waiting\n");												/**<Information*/

	Message_Queue = mq_open("/msg_queue",O_CREAT | O_RDWR, 0666, NULL);			/**<Create a message queue*/
	if(Message_Queue == -1)
		perror("Error creating a POSIX msg queue\n"
				"Try increasing the size of the queue in POSIX.\n"
				"To increase the size type \"ulimit -q <size>\"\n");			/**<Error message if queue can not be created*/

	printf("Press enter whenever you want to reply");
	fsync(1);

	while(1)
	{
		if(iBreak_Time == 1)													/**<If this variable is set*/
		{
			if(mq_receive(Message_Queue,chQueue_Msg,BUFSIZ,NULL) == -1)			/**<Receive a message from the child process*/
				perror("Error receiving Message");								/**<Error message*/
			if(strstr(chQueue_Msg,"is leaving\n") != NULL)						/**<Checking the string*/
			{
				strtok(chQueue_Msg,"\n");										/**<Extract the user name from the message*/
				printf("%s",chQueue_Msg);										/**<Debug print*/
				fsync(1);														/**<Sync the output*/
				for(iLocal = 0; iLocal < iNum_Connections; iLocal++)			/**<Loop until found in the stored user name*/
					if(strcmp(List_Users[iLocal].chConnected_User,				/**<Compare the user name with received message*/
							chQueue_Msg) == 0)
						break;													/**<Break if found*/
				for(;iLocal < 5;iLocal++)										/**<Delete the matched content*/
					List_Users[iLocal] = List_Users[iLocal+1];					/**<Shift all higher number array data to lower number array*/
			}
			if(strcmp(chQueue_Msg,"Client is disconnecting\n") == 0)			/**<Check what is the received msg*/
			{
				memset(chQueue_Msg,0x00,100);									/**<Clean the msg so that it doesnt come again unneccesarly*/
				printf("%s",chQueue_Msg);										/**<Print the message passed by the child client*/
				iNum_Connections--;												/**<Decrease the number of connection*/
				for(iLocal = 0; iLocal < iNum_Connections; iLocal++)			/**<Scans all the available users*/
				{
					printf("%s on %d",List_Users[iLocal].chConnected_User,		/**<Print the information of the users*/
							List_Users[iLocal].iSocket_Number);
					fsync(1);													/**<Sync the standard output with program*/
				}
			}
			if(iNum_Connections == 0)											/**<If number of connection is found to be 0 then terminate the program*/
				break;
			FD_ZERO(&Terminal_Fds);												/**<Clean the file descriptor*/
			FD_SET(0, &Terminal_Fds);											/**<Set the sever "who accepts the connection" to the file descriptors*/

			Scan_Input.tv_sec = 2;												/**<2 sec timer*/
			Scan_Input.tv_usec = 0;												/**<0 micro second*/

			iRet_Val = select(1,&Terminal_Fds,NULL,NULL,&Scan_Input);			/**<Set a value specified in above time out struct*/
			if(iRet_Val == -1)													/**<Error message*/
				perror("Error in select()");
			else if(iRet_Val)
			{
				int		iFound = 0;												/**<Intialization of variable*/

				getchar();														/**<Get a single character from the user*/
				for(iLocal = 0; iLocal < iNum_Connections;iLocal++)				/**<Print all connected users*/
					printf("Available User: %s\n",
						List_Users[iLocal].chConnected_User);

				printf("If you want to reply then type user name"
						" or \"NO\" to skip:");									/**<Information message*/
				fgets(chRead_Buf,100,stdin);									/**<Reads the stdin for data*/
				strtok(chRead_Buf,"\n");										/**<Get the user name only*/
				for(iLocal = 0;iLocal < iNum_Connections;iLocal++)				/**<Scans for the user name in stored users*/
					if(strcmp(List_Users[iLocal].chConnected_User,
							chRead_Buf) == 0)
						{
							iFound = 1;											/**<If found set it*/
							break;												/**<Break the loop*/
						}
				if(iFound == 1)													/**<If found then enter*/
				{
					iFound = 0;													/**<Clear the variable*/
					printf("Type the msg:");									/**<User information*/
					fsync(1);													/**<Sync the output with stdout*/
					fgets(chRead_Buf,100,stdin);								/**<Read the data from the user*/
					fsync(1);													/**<Sync with the input*/
					memset(chMessage+iMsg_Len,0x00,sizeof(chMessage)-iMsg_Len);	/**<Clean the message*/
					strcpy(chMessage+iMsg_Len,chRead_Buf);						/**<Copy the read message in*/
					iClient_Sockfd = List_Users[iLocal].iSocket_Number;			/**<Set the socket fd*/
					write(iClient_Sockfd,chMessage,strlen(chMessage));			/**<Write data to client*/
					fsync(iClient_Sockfd);										/**<Sync with the client*/
				}
				memset(chRead_Buf,0x00,sizeof(chRead_Buf));						/**<Clean the Read buffer*/
			}
		}

		Connection_Accept_Time.tv_sec = 1;										/**<Time out value of 1 seconds*/
		Connection_Accept_Time.tv_usec = 500000;								/**<Time out value of 1.5 seconds*/

		FD_ZERO(&Accept_Fds);													/**<Clean the file descriptor*/
		FD_SET(iServer_Sockfd, &Accept_Fds);									/**<Set the sever "who accepts the connection" to the file descriptors*/

		iRet_Val = select(100,&Accept_Fds,NULL,NULL,&Connection_Accept_Time);	/**<Set a value specified in above time out struct*/
		if(iRet_Val == -1)														/**<Error if return value is -1*/
			perror("Read time out selection occurred an error");				/**<Error msg*/
		else if(iRet_Val)
		{
			iClient_Len = sizeof(Client_Socket);								/**<Client socket size*/
			iClient_Sockfd = accept(iServer_Sockfd,								/**<Accepts the connection from a client*/
									(struct sockaddr *)&Client_Socket,
									(socklen_t *)&iClient_Len);
			printf("Client joined on port %d\n",Client_Socket.sin_port);		/**<Print the information regarding the connection established*/
			iBreak_Time = 1;													/**<Set the variable so that it will next time check whether to break or not*/
			iNum_Connections++;													/**<Increament the connection*/
			fsync(iClient_Sockfd);												/**<Sync with the client*/
			read(iClient_Sockfd,chClient_User,sizeof(chClient_User));			/**<Read Client pc's user name*/
			strncpy(List_Users[iNum_Connections-1].chConnected_User				/**<Copy the buffer in List*/
					,chClient_User,strlen(chClient_User));
			List_Users[iNum_Connections-1].iSocket_Number = iClient_Sockfd;		/**<Copy the socket number in List*/
		}
		else
			continue;															/**<Continue from while(1)*/


		Child_Process = fork();													/**<Create a child*/
		if(Child_Process == -1)
		{
			perror("Can not create child process");								/**<Error msg*/
		}
		else if(Child_Process == 0)
		{
			char		chBuffer[100];											/**<Read buffer for client*/
			Time_Out_t	Socket_Time_Out;										/**<Time out struct object for accepting connection*/
			fd_set		Socket_Fds;												/**<File descriptor of the above mentioned timeout*/

			if(close(iServer_Sockfd) == -1)										/**<Close the duplicate file descriptor*/
				perror("Child can not proceed");								/**<Error msg*/

			Message_Queue = mq_open("/msg_queue",O_RDWR);

			while(1)
			{
				FD_ZERO(&Socket_Fds);											/**<Clean the file descriptor*/
				FD_SET(iClient_Sockfd, &Socket_Fds);							/**<Set the sever "who accepts the connection" to the file descriptors*/

				Socket_Time_Out.tv_sec = 1;										/**<Set the timer to 1 sec*/
				Socket_Time_Out.tv_usec = 500000;								/**<Add .5 second to timer*/

				iRet_Val = select(iClient_Sockfd+1
						,&Socket_Fds,NULL,NULL,&Socket_Time_Out);				/**<Set a value specified in above time out struct*/
				if(iRet_Val == -1)
					perror("Error in select()");								/**<Error message*/
				else if(iRet_Val)
				{
					memset(chBuffer,0x00,sizeof(chBuffer));						/**<Clean the message buffer*/
					read(iClient_Sockfd,chBuffer,sizeof(chBuffer));				/**<Read the Buffer*/
					if(strstr(chBuffer,"exit\n") != NULL)						/**<If exit scanned*/
						break;													/**<Break the loop*/

					printf("%s",chBuffer);										/**<Print the client's message to screen*/
					fsync(1);													/**<Sync with the stdout*/
					memset(chBuffer,0x00,sizeof(chBuffer));						/**<Clean the buffer*/
				}

				strcpy(chQueue_Msg,"abcd\n");									/**<Copy garbage in to message queue*/

				if(mq_send(Message_Queue,chQueue_Msg,BUFSIZ,0) == -1)			/**<And send so that parent does not block it self*/
					perror("Error in sending msg in child");					/**<Error messsage*/
			}

			sprintf(chQueue_Msg,"%s is leaving\n",chClient_User);				/**<Print the message*/
			printf("%s",chQueue_Msg);											/**<Debug print*/
			fsync(1);															/**<Sync the stdout*/

			iRet_Val = mq_send(Message_Queue,chQueue_Msg,100,10);				/**<Send the leaving message to parent*/
			if(iRet_Val == -1)
				perror("Error in sending msg in child");						/**<Error in sending*/
			else if(iRet_Val == 0)
				printf("Msg sending successful\n");								/**<Success in sending*/

			strcpy(chQueue_Msg,"Client is disconnecting\n");					/**<Copy the data in to Message queue structure*/

			iRet_Val = mq_send(Message_Queue,chQueue_Msg,100,1);				/**<Send the disconnection msg to parent*/
			if(iRet_Val == -1)
				perror("Error in sending msg in child");						/**<Error in sending*/
			else if(iRet_Val == 0)
				printf("Msg sending successful\n");								/**<Success in sending*/

			if(mq_close(Message_Queue) == -1)									/**<Close the message queue*/
				perror("Error in closing a MSG Queue");							/**<Error in closing the message queue*/

			if(close(iClient_Sockfd) == -1)										/**<Close client descriptors*/
				fprintf(stderr,
						"Error in closing the %d client socket",				/**<Error in closing the Client socket*/
						iClient_Sockfd);
			printf("Child Terminated...\n");									/**<Child is terminated*/
			exit(EXIT_SUCCESS);													/**<Exit with success*/
		}
	}

	if(shutdown(iServer_Sockfd,2) == -1)										/**<Shutdown the socket and reading and writting is prohibited*/
		perror("Error in shutdown()");											/**<Error message*/

	if(close(iServer_Sockfd) == -1)												/**<Close the server socket*/
		perror("Error in closing the server socket.");							/**<Error message*/

	if(mq_close(Message_Queue) == -1)											/**<Close the message queue*/
	{
		perror("Error in closing the message queue");							/**<Error message*/
		exit(EXIT_FAILURE);
	}

	if(mq_unlink("/msg_queue") == -1)											/**<Remove the message queue*/
	{
		perror("mq_unlink()");													/**<Error message*/
		exit(EXIT_FAILURE);
	}

	printf("\nTerminating\n");
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
	FILE	*fptrRead_User_Name;												/**<File pointer for reading name*/
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



/*
 * @brief	Creates and sets up the listen queue
 * @param	None
 * @retval	None
 *
 * This function is used to create a socket for the server which will
 * bind to the address mentioned in the function and make a listning queue
 * so that any client willing to connect can connect.
 *
 * There are no parameters to be passed as this function is using the one
 * and only one varaible that is Server_Address which is defined globally
 *
 * This function does not return anything as everything that will be written
 * in to global variable and this variable can be accessed throgh the program
 */
void Connect_Socket_Server(void)
{
	int 		iServer_Len;													/**<Length of server socket*/
	int			iPort_Num;														/**<Integer port number*/
	char		chPort_Num[7];													/**<Character array port number*/

	memset(chPort_Num,0x00,sizeof(chPort_Num));

	iServer_Sockfd = socket(AF_INET, SOCK_STREAM, 0);							/**<Creates a socket for server*/
	if(iServer_Sockfd == -1)
	{
		fprintf(stderr,"Socket creation failed in server. "						/**<Error in creating a socket*/
				"Program will terminate.\n");
		exit(EXIT_FAILURE);														/**<Exit the program as no other function can work*/
	}


	printf("Enter port number: ");												/**<Ask to user for port number*/
	fgets(chPort_Num,7,stdin);													/**<Get the port number*/
	strtok(chPort_Num,"\n");													/**<Eliminate the last \n character*/
	iPort_Num = atoi(chPort_Num);												/**<Convert port number array to integer*/

	Server_Address.sin_family = AF_INET;										/**<Setting values in structure*/
	Server_Address.sin_addr.s_addr = htonl(INADDR_ANY);							/**<Accepts any IP*/
	Server_Address.sin_port = htons(iPort_Num);									/**<Accepts connection on this port*/
	iServer_Len = sizeof(Server_Address);

	if(bind(iServer_Sockfd,
			(struct sockaddr *)&Server_Address, iServer_Len) == -1)				/**<Bind the socket_fd to Server_Socker*/
		perror("Error on bind()");

	if(listen(iServer_Sockfd, 5) == -1)											/**<Listen the clients maximum of 5*/
		perror("Error in listen()");
}
