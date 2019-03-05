Client_app: Client.o
	@echo 'Compiling the Server application '
	@echo 'Final executable name is "$@"'
	gcc -Wall -o Client_app Client.o
	@echo ''

Client.o: Client.c
	@echo ''
	@echo 'Compiling the client.c file'
	gcc -I$(INCLUDE2) -Wall -c Client.c
	@echo ''

