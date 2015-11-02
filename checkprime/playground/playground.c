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
	int fd[2],n=10;
	char string[]="dickbutt.";

	if (pipe(fd)<0){
			perror("Fehler beim Erstellen der Pipe.\n");
			return EXIT_FAILURE;
	}


	pid = fork();
	if (pid < 0){
		fprintf(stderr,"Fehler beim fork().\n");
		return EXIT_FAILURE;
	}
	else if (pid == 0){
		printf("This is the child process.\n");
		printf("and this is mit pid: <%d>\n",pid);
		printPI();
		close(fd[1]); // stop writing
		char *penis;
		n = read (fd[0],penis,PIPE_BUF); // leseseite auslesen
		printf("I just received <%s> through the pipe.\n",penis);
/*		n = read (fd[0],string,PIPE_BUF); // leseseite auslesen
		if((write(STDOUT_FILENO,string,n))!=n){
			fprintf(stderr,"Fehler bei write().\n");
		return EXIT_FAILURE;
		}
	*/
		printf("\n");
	}
	else {
//		printf("This is the parent process.\n");
		printf("This is the parent process and I'm writing stuff into the pipe\nThis is mit pid: <%d>\n",pid);
		printPI();
		close(fd[0]); // stop reading
		if ((write(fd[1],string,n)) !=n){
			perror("Fehler beim Schreiben in die Pipe.\n");
			return EXIT_FAILURE;
		}
		else{
			printf("I just wrote <%s> into the pipe.\nNow I'm gonna try to wait for my child (pid: <%d>) to terminate.\n\n",string,pid);
		}
		if (waitpid(pid,NULL,0) != pid){
			perror("Fehler beim warten auf das Kindprozess.\n");
			return EXIT_FAILURE;
			}
			else{
				printf("[parent] My child process just terminated and I'm gonna terminate now, too.\n");
			}
	}
	return EXIT_SUCCESS;
//	return 0;
}
