#This is the make file for generating the final executable for Book_Keeping program

Book_Keeping: main.o
	@echo ''
	@echo 'This generate a final executable file'
	@echo 'with name "$@"'
	gcc -Wall -o Book_Keeping main.o -lpthread
	@echo ''
	
main.o: main.c
	@echo ''
	@echo 'This will compile the main.c file'
	gcc -Wall -c -lpthread main.c
	@echo ''
	
clean:
	@echo ''
	@echo 'This will clean the generated object files'
	rm -rf *.o
	@echo ''