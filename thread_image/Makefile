label:
	gcc -c imagec.c
	g++ -c jpeg.cpp -std=c++11
	g++ imagec.o jpeg.o -o exe -lpthread `pkg-config --cflags --libs opencv`
clean:
	rm *.o *exe