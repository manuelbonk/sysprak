#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void printPI(){
	printf("PID:%4d\nPPID:%4d\nUID:%4d\n\n",getpid(),getppid(),getuid());
}

int main (int argc, char *argv[]){
	pid_t pid;
	pid = fork();
	if (pid < 0){
		fprintf(stderr,"Fehler beim fork().\n");
	}
	else if (pid == 0){
		printf("This is the child process.\n");
		printf("and this is mit pid: %d\n",pid);
		printPI();
	}
	else {
		if (waitpid(pid,NULL,0) != pid){
			perror("Fehler beim warten auf das Kindprozess\n");
			return EXIT_FAILURE;
			}
		printf("This is the parent process.\n");
		printf("and this is mit pid: %d\n",pid);
		printPI();
	}
	return 0;
}
