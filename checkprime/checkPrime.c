#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void printPI(){
	printf("PID:%4d\nPPID:%4d\nUID:%4d\n\n",getpid(),getppid(),getuid());
	for (int i=0;i<42;i++){
		printf("%2d\n",i);
	}
}


int main (int argc, char *argv[]){
	printPI();
	fork();
	printPI();
	return 0;
}
