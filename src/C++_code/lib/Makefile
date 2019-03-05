path= ../linking
label:
		#gcc -c PS_lib.c
		#ar  rcs $(path)/libPS_lib.a PS_lib.o  //for static binding
		gcc -g0 -fPIC -Wall -Werror -Wextra -pedantic *.c -shared -o $(path)/libPS_lib.so
		
clean:
		rm *.o $(path)/libPS_lib.so
		