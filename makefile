a: main.o read.o
	g++ main.o read.o -o a
main.o: main.cpp read.cpp read.h
	g++ -c main.cpp
read.o: read.cpp read.h
	g++ -c read.cpp
