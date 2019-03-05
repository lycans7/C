/*
 * main.c
 *
 *  Created on: 04-Aug-2015
 *      Author: tejas
 */


#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	<stdlib.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>

#define 	BUFLEN 		512  													/*	Max length of buffer*/
#define 	PORT 		8888   													/*	The port on which to listen for incoming data*/


typedef struct sockaddr_in Socket_t;											/*	structure is renamed for shorter name in program*/


int main(void)
{
	Socket_t 	Server_Socket, Client_Socket;									/*	Client and Server socket structures*/
	int			iSocket_Len = sizeof(Client_Socket);							/*	Client socket length*/
	int 		iSock_Fd;														/*	This variable holds the file descriptor for Server socket*/
	int			iPort_Count = 0;												/*	This variable holds the count of clients connected to server*/
	int			iRcv_Len;														/*	This variable holds the count of data received from client*/
	int 		iLocal;															/*	Local variable*/
	char 		chBuffer[BUFLEN];												/*	Message passing buffer*/
	char		chPorts[10][6];													/*	Different ports are held here*/

	memset(chPorts,0x00,sizeof(chPorts));										/*	Setting the chPorts to 0*/

	printf("In this program UDP sockets are used as in UDP,\n"
			"it is not required to remain connected and as many\n"
			"clients can get connected as you want this one is \n"
			"is simple to handle.\n"
			"Press any key to continue...\n");
	getchar();

	iSock_Fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);						/*	Creating a socket.*/
    if (iSock_Fd == -1)
    {
        perror("Error in creating socket\n");									/*	Error message*/
    }

    memset((char *)&Server_Socket,0,sizeof(Server_Socket));						/*	Cleaning all the garbage details in Server_socket structure object*/

    Server_Socket.sin_family = AF_INET;											/*	Setting structure data*/
    Server_Socket.sin_port = htons(PORT);
    Server_Socket.sin_addr.s_addr = htonl(INADDR_ANY);


    if(bind(iSock_Fd,															/*	Bind the socket to the server*/
    		(struct sockaddr*)&Server_Socket,
    		sizeof(Server_Socket)) == -1)
    {
    	perror("Error in binding the socket\n");								/*	Error message*/
    }

    while(1)
    {
        if ((iRcv_Len = recvfrom(iSock_Fd,										/*	Receives data from client*/
        						 chBuffer,
        						 BUFLEN,0,
        						 (struct sockaddr *)&Client_Socket,
        						 (socklen_t *)&iSocket_Len)) == -1)
        {
            perror("Error in receiving the data from the client.\n");			/*	Error message*/
        }

        printf("Received packet from %s:%d\n",									/*	Debug string that mentions the port and ip of the connected client*/
        		inet_ntoa(Client_Socket.sin_addr),
        		ntohs(Client_Socket.sin_port));


        if(iPort_Count == 0)													/*	If port count is 0 than copy the new incoming data's port number*/
        {
			sprintf(chPorts[iPort_Count],"%d",ntohs(Client_Socket.sin_port));	/*	Copies the client's port number in buffer*/
			iPort_Count++;
        }
        else
        {
        	sprintf(chPorts[iPort_Count],"%d",ntohs(Client_Socket.sin_port));	/*	Copies the client's port number in buffer*/
        	iPort_Count++;														/*	Increament the count*/
        	for(iLocal = 0; iLocal < iPort_Count-1; iLocal++)					/*	Scan all the connected clients for their port*/
        		if(strcmp(chPorts[iLocal],chPorts[iPort_Count-1]) == 0)			/*	If port matches than client is already connected*/
        			iPort_Count--;												/*	So make the count decreamented by 1*/

        }

        if (sendto(iSock_Fd,													/*	Reply to client with the data*/
        		   chBuffer,
        		   iRcv_Len,0,
        		   (struct sockaddr*)&Client_Socket,
        		   iSocket_Len) == -1)
        {
            perror("Error in sending the data to the client.\n");				/*	Error in sending data*/
        }

        if(strncmp(chBuffer,"quit",4) == 0 && iPort_Count > 0)					/*	Checks if the client is requesting to quit*/
        	iPort_Count--;														/*	Decreament the port count as 1 client has left*/
        if(iPort_Count == 0)													/*	If all clients has left*/
        	break;																/*	Break the loop*/
    }

    if(close(iSock_Fd) == -1)													/*	Closing the Server socket created earlier*/
    	perror("Error in closing the socket.\n");								/*	Error message*/
    printf("Terminating.....\n");
    return 0;
}
