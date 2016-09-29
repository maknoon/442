CC=gcc
CCFLAGS= -g -Wall

freq: frequency.o
	$(CC) $(CFLAGS) -o freq frequency.c 

play: playfair.o playfairHelper.o
	$(CC) $(CFLAGS) -o play playfair.c playfairHelper.c

clean:
	rm freq frequency.o play playfair.o playfairHelper.o
