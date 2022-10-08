CC = g++
CFLAG= -Wall

all: main

main: main.o HashMap.hpp
	$(CC) $(Wall) -g -o main main.o 

main.o: main.cpp
	$(CC) $(Wall) -c main.cpp

clean:
	rm -rf *.o main