CC = gcc
CFLAGS = -Wall -fPIC

all : testExo

testExo : testExo.o exo.o
	$(CC) -o testExo testExo.o exo.o

testExo.o : testExo.c exo.h
	$(CC) -c $(CFLAGS) testExo.c

exo.o : exo.c exo.h
	$(CC) -c $(CFLAGS) exo.c

clean:
	rm -f testExo *.o
