#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS		3


typedef struct{
	long tid;
	long long unsigned value;
}threadParams;

long long unsigned factor=1;
pthread_mutex_t mutexfactor;

struct timespec tim,tim2;

	////////////////////////////////////////////////////////////////////////
	// LOOK FOR FACTORS ////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
void *checkPrime(void *penis){
	threadParams *tp = penis;
	for(long long unsigned i=2+tp->tid;i<sqrtl(tp->value);i+=NUM_THREADS){
//		printf("<%llu>: val: <%d>\n",tp->tid,i);
		if(factor>1){
			printf("yay, es wurde ein teiler von einem anderen thread gefunden!\n");
			pthread_exit(NULL);
		}
		if(tp->value % i == 0){
			printf("<%ld>: <%llu> ist ein Teiler von <%llu>!\n",tp->tid,i,tp->value);
			pthread_mutex_lock(&mutexfactor);
			factor = i;
			pthread_mutex_unlock(&mutexfactor);
			pthread_exit((void*)i);
		}
//	printf("<%lld>\n",i);
// even if the thread sleeps for only 1 ns, the speed decrease is ridiculous
//	nanosleep(&tim,&tim2);
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
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	//return code of thread creation
	int rc;
	long t;
	void *status;
	tim.tv_nsec=1;


	////////////////////////////////////////////////////////////////////////
	// CREATE THREADS //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
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
	pthread_attr_destroy(&attr);

	////////////////////////////////////////////////////////////////////////
	// WAIT FOR THE THREADS TO END /////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	for (t=0;t<NUM_THREADS;t++) {
		rc = pthread_join(threads[t],&status);
		if (rc) {
			printf("ERROR: return code from pthread_join(): <%d>\n",rc);
			exit(-1);
		}
		printf("return from thread[%ld]: <%llu>\n",t,(long long unsigned)status);
	}
	if (factor == 1){
		printf("<%llu> is prime!\n",value);
	}
	pthread_exit(NULL);
	return 0;
}
