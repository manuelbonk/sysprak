CFLAGS = -g -Wall -lm -pthread
CC = gcc

default: checkPrimeMultithreaded

checkPrimeMultithreaded: checkPrimeMultithreaded.c
	$(CC) $(CFLAGS) -o checkPrimeMultithreaded checkPrimeMultithreaded.c

clean:
	rm -f checkPrimeMultithreaded
