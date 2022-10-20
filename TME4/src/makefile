CC = g++
CFLAG = -Wall

all: main

main: main.o Compte.o Banque.o
	$(CC) $(CFLAG) -o main main.o Compte.o Banque.o

main.o: main.cpp Banque.h Compte.h
	$(CC) $(CFLAG) -c -pthread main.cpp

Compte.o: Compte.cpp  Compte.h
	$(CC) $(CFLAG) -c Compte.cpp

Banque.o: Banque.cpp Banque.h
	$(CC) $(CFLAG) -c Banque.cpp
	


clean:
	rm -f *.o main

