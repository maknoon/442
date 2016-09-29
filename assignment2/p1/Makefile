CC=gcc
CCFLAGS= -g -Wall

freq: frequency.o
	$(CC) $(CFLAGS) -o freq frequency.c 

decr: decrypt.o
	$(CC) $(CFLAGS) -o decr decrypt.c

clean:
	rm freq frequency.o decr decrypt.o
