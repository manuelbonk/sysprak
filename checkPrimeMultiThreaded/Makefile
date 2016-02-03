CFLAGS = -g -Wall -lm -pthread
CC = gcc

default: checkPrimeMultiThreaded

checkPrimeMultithreaded: checkPrimeMultiThreaded.c
	$(CC) $(CFLAGS) -o checkPrimeMultiThreaded checkPrimeMultiThreaded.c

clean:
	rm -f checkPrimeMultiThreaded
