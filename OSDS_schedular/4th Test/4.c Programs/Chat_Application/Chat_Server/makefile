#Make file for Server program of Chat application

Chat_Server: Chat_Server.o
	@echo ' '
	@echo 'This will compile the final executable'
	@echo 'with name "$@"'
	gcc -Wall -o Chat_Server Chat_Server.o -lrt
	@echo ' '
	
Chat_Server.o: Chat_Server.c
	@echo ' '
	@echo 'This will compile the main file'
	gcc -Wall -c Chat_Server.c -lrt
	@echo ' '
	
clean:
	@echo ' '
	@echo 'This will clean the generated objects'
	rm -rf *.o
	@echo ' '