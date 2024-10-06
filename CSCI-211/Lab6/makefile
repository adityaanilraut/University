# Makefile to compile and link main.cpp, linkedlist.cpp, linkedlist.h

# Target to generate the final executable
main: linkedlist.o main.o
	g++ -Wall -pedantic -g -o main linkedlist.o main.o

# Rule to compile main.cpp
main.o: main.cpp linkedlist.h
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

# Rule to compile linkedlist.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -Wall -pedantic -g -std=c++11 -c linkedlist.cpp

# Rule to clean up object files and executables
clean:
	rm -f *.o main main.exe