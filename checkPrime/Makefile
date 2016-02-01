CFLAGS = -g -Wall -lm
CC = gcc

checkPrime: checkPrime.c
	$(CC) $(CFLAGS) -o checkPrime checkPrime.c

play: default
	./checkPrime 2135435246

clean:
	rm -f checkPrime

default: checkPrime
