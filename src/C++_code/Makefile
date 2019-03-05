lib= linking
path= src
exe= executable
l= lib

label:
		make -C $(l)
		#g++ $(path)/My_project.cpp -o $(exe)/exe -L$(lib) -lPS_lib //static linking
		g++ $(path)/My_project.cpp -o $(exe)/exe -fPIC -L./$(lib) -lPS_lib
clean:
		rm $(exe)/exe *.o $(path)/My_project.o 