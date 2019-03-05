#Make file for Client application

Chat_Client: Chat_Client.o
	@echo ' '
	@echo 'This will compile the final executable'
	@echo 'with name "$@"'
	gcc -Wall -o Chat_Client Chat_Client.o
	@echo ' '
	
Chat_Client.o: Chat_Client.c
	@echo ' '
	@echo 'This will compile the main file'
	gcc -Wall -c Chat_Client.c
	@echo ' '
	
clean:
	@echo ' '
	@echo 'This will clean the generated objects'
	rm -rf *.o
	@echo ' '