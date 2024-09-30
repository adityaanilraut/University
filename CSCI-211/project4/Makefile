
calc: calc.o dstack.o
	g++ -Wall -pedantic -g -o calc calc.o dstack.o

dstack.o: dstack.h dstack.cpp
	g++ -Wall -pedantic -g -std=c++11 -c dstack.cpp

calc.o: dstack.h calc.cpp
	g++ -Wall -pedantic -g -std=c++11 -c calc.cpp

clean:
	rm -f calc calc.exe calc.o dstack.o
