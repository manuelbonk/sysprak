#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	pid_t pid;
	mkfifo("./penis",644);
	return 0;
}
