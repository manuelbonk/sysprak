#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>


void printPI(){
	printf("PID:%4d\nPPID:%4d\nUID:%4d\n",getpid(),getppid(),getuid());
}

int main (int argc, char *argv[]){
	pid_t pid;
	int fd[2],n=sizeof(long long unsigned);
//	char *string = malloc(n*sizeof(char));
	unsigned long long string=0;
//	int string=malloc(sizeof(unsigned long long));

		//////////////////////////////////////////////////////////////////////////////////
		///ERROR HANDLING/////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////
	if (pipe(fd)<0){
			perror("Fehler beim Erstellen der Pipe.\n");
			exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0){
		fprintf(stderr,"Fehler beim fork().\n");
		exit(EXIT_FAILURE);
	}

	else if (pid>0){
		//////////////////////////////////////////////////////////////////////////////////
		///PARENT PROCESS/////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////
		printf("This is the parent process and I'm writing stuff into the pipe\nThis is mit pid: <%d>\n",pid);
		string = 112312412412412323;
//		string = "dickbutt.";
//		printPI();
		close(fd[0]); // stop reading
		if ((write(fd[1],&string,n)) !=n){
//		if ((write(fd[1],string,n)) !=n){
			perror("Fehler beim Schreiben in die Pipe.\n");
			exit(EXIT_FAILURE);
		}
		else{
			printf("I just wrote <%llu> into the pipe.\nNow I'm gonna try to wait for my child (pid: <%d>) to terminate.\n\n",string,pid);
//			printf("I just wrote <%s> into the pipe.\nNow I'm gonna try to wait for my child (pid: <%llu>) to terminate.\n\n",string,pid);
		}
		if (waitpid(pid,NULL,0) != pid){
			perror("Fehler beim warten auf das Kindprozess.\n");
			exit(EXIT_FAILURE);
			}
			else{
				printf("[parent] My child process just terminated and I'm gonna terminate now, too.\n");
			}
	}
	else {
		//////////////////////////////////////////////////////////////////////////////////
		///CHILD PROCESS//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////
		printf("This is the child process.\n");
		printf("and this is mit pid: <%d>\n",pid);
//		printPI();
		close(fd[1]); // stop writing
		n = read (fd[0],&string,PIPE_BUF); // read pipe
//		n = read (fd[0],string,PIPE_BUF); // read pipe
		printf("I just received <%llu> through the pipe.\n",string);
//		printf("I just received <%s> through the pipe.\n",string);
		printf("\n");
	}
	return EXIT_SUCCESS;
}
