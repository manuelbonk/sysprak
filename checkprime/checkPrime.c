#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>


void printPI(){
	printf("PID:%4d\nPPID:%4d\nUID:%4d\n\n",getpid(),getppid(),getuid());
}

int main (int argc, char *argv[]){

	srand(time(NULL));
	unsigned long long p = rand();
	unsigned long long lowerBorder = 2;
	unsigned long long upperBorder = sqrtl(p);
	unsigned long long result=0;
	printf("upper border: <%llu>\n",upperBorder);

	//////////////////////////////////////////////////////////////////////////////////
	///ERROR HANDLING/////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	pid_t pid;
	int fd[2],n=sizeof(long long unsigned);

	if (pipe(fd)<0){
			perror("Fehler beim Erstellen der Pipe.\n");
			exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0){
		fprintf(stderr,"Fehler beim fork().\n");
		exit(EXIT_FAILURE);
	}

	//////////////////////////////////////////////////////////////////////////////////
	///CHILD PROCESS//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	else if (pid == 0){
		printf("\nThis is the child process.\n");
		for(unsigned long long i=lowerBorder;i<upperBorder;i+=2){
			if (p % i == 0){
				printf("<%llu> ist ein Teiler von <%llu>!\n",i,p);
				result = i;
			i=upperBorder;
			}
		}
		close(fd[0]); // stop reading
		if ((write(fd[1],&result,n))!= n){ // write i into the pipe
			perror("Error: couldn't write to the pipe.\n");
			exit(EXIT_FAILURE);
		}
		else {
				printf("I've just wrote <%llu> in the pipe.\n",result);
			}
		close(fd[1]);
	}

	//////////////////////////////////////////////////////////////////////////////////
	///PARENT PROCESS/////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	else {
		printf("This is the parent process.\nI'm gonna wait for my child process to terminate.\n");
		if (waitpid(pid,NULL,0) != pid){ // waiting for the child process to terminate
			perror("Fehler beim warten auf das Kindprozess\n");
			exit (EXIT_FAILURE);
		}
		printf("\nThis is the parent process again.\n");

		close(fd[1]); // stop writing
		n = read(fd[0],&result,n); // read the pipe
		printf("I've just received <%llu> through the pipe.\n",result);

		for(unsigned long long i=lowerBorder+1;i<upperBorder;i+=2){
			if (p % i == 0){
				result = i;
			}
		}
		if (result != 0){
			printf("<%llu> is not prime!\n",p);
		}
		else {
			printf("<%llu> is prime!\n",p);
		}
	close(fd[0]);
	}
	return 0;
}
