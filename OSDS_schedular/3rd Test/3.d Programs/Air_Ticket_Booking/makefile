#This is a make file for air ticket booking program

Booking: main.o
	@echo ' '
	@echo 'This will compile the final executable'
	@echo 'with name "$@"'
	gcc -Wall -o Booking main.o -lpthread
	@echo ' '
	
main.o: main.c
	@echo ' '
	@echo 'This will compile the main.c file'
	gcc -Wall -c main.c -lpthread
	@echo ' '
	
clean:
	@echo ' '
	@echo 'This will clean all the generated files Execpt final executable'
	rm -rf *.o
	@echo ' '
	
clean_all:
	@echo ' '
	@echo 'This will clean all the generated files'
	rm -rf *.o
	rm -rf Booking
	@echo ' '