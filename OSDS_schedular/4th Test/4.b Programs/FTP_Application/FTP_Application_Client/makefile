#this is a make file for compiling the FTP Client app

FTP_Client: FTP_App_Client.o
	@echo ''
	@echo 'This will make a final executable with name "$@"'
	gcc -Wall -o FTP_Client FTP_App_Client.o
	@echo ''
	
FTP_App_Client.o: FTP_App_Client.c
	@echo ''
	@echo 'This will compile a main file'
	gcc -Wall -c FTP_App_Client.c 
	@echo ''
		
	
clean:
	rm -rf *.o