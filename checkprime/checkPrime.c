#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void printPI(){
	printf("PID:%4d\nPPID:%4d\nUID:%4d\n\n",getpid(),getppid(),getuid());
}


int main (int argc, char *argv[]){
	printPI();
	fork();
	printPI();
	return 0;
}
