CFLAGS = -g -Wall -lm -pthread -std=c99
CC = gcc

default: checkPrimeMultiThreaded

checkPrimeMultithreaded: checkPrimeMultiThreaded.c
	$(CC) $(CFLAGS) -o checkPrimeMultiThreaded checkPrimeMultiThreaded.c

clean:
	rm -f checkPrimeMultiThreaded
