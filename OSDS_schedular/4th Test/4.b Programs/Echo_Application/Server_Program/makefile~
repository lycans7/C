#This is a common make file for compiling the client and server programs.

Server_app: Server.o
	@echo 'Compiling the Server application '
	@echo 'Final executable name is "$@"'
	gcc -Wall -o Server_app Server.o
	@echo ''

Server.o: Server.c
	@echo ''
	@echo 'Compiling the server.c file'
	gcc -Wall -c Server.c
	@echo ''


