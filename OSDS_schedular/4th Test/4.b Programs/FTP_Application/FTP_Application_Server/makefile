#this is a make file for compiling the FTP Server app

FTP_Server: FTP_App_Server.o FTP_Functions.o Dir.o
	@echo ''
	@echo 'This will make a final executable with name "$@"'
	gcc -Wall -o FTP_Server FTP_App_Server.o FTP_Functions.o Dir.o
	@echo ''
	
FTP_App_Server.o: FTP_App_Server.c FTP_Functions.h Dir.h
	@echo ''
	@echo 'This will compile a main file'
	gcc -Wall -c FTP_App_Server.c 
	@echo ''
	
FTP_Functions.o: FTP_Functions.c FTP_Functions.h Dir.h
	@echo ''
	@echo 'This will compile a supporting header file'
	gcc -Wall -c FTP_Functions.c
	@echo ''
	
Dir.o: Dir.c Dir.h
	@echo ''
	@echo 'This will compile a supporting header file'
	gcc -Wall -c Dir.c
	@echo ''
	
	
clean:
	rm -rf *.o