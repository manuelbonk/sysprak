#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define NUM_THREADS		4


typedef struct{
	long tid;
	long long unsigned value;
}threadParams;


void *checkPrime(void *penis){
	printf("pthread_self(): <%lu>\n",pthread_self());
	threadParams *tp = penis;
	for(long long unsigned i=2+tp->tid;i<sqrtl(tp->value);i+=NUM_THREADS){
//		printf("<%llu>: val: <%d>\n",tp->tid,i);
		if(tp->value % i == 0){
			printf("<%ld>: <%llu> ist ein Teiler von <%llu>!\n",tp->tid,i,tp->value);
			return 0;
		}
	}
	pthread_exit(NULL);
}

int main (int argc, char *argv[]){
	// check parameters
	long long unsigned value;
	if (argc>1){
		value= strtoull(argv[1],NULL,10);
	}
	else {
		srand(time(NULL));
		value = rand();
		}

	threadParams tp[NUM_THREADS];
	// initialize and set thread detached attribute
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	//return code of thread creation
	int rc;
	long t;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	for (t=0;t<NUM_THREADS;t++){
		tp[t].tid=t;
		tp[t].value=value;
		printf("creating thread <%ld>\n",t);
		rc = pthread_create(&threads[t],&attr,checkPrime,&tp[t]);
		if (rc) {
			printf("ERROR: return code from pthread_create(): <%d>\n",rc);
			exit(-1);
		}
	}
/*
	while(argc>0){
		printf("the parent process is still alive!\n");
		sleep(1);
	}
*/

	pthread_exit(NULL);
	return 0;
}
