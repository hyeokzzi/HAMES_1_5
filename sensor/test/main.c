#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 2


//variable
ACK = 0;
BACK = 0;


void *threadFunc(void *threadID){
	int tid = *((int *)threadID);
	
	for (int i=1;i<=10; i++){
		printf("Thread %d: %d\n", tid, i);
	}

	pthread_exit(NULL);
}

void sensorThread(){
  int cnt = 0;
  int nowACK = 0;
  
  //MAKE
  printf("Make thread\n");
  
  while(1){
    if (nowACK == 0) continue;
    else {
      printf("A: d\", cnt);
      cnt++;
      sleep(1);
    }
  }
}

void 

int main(){
	pthread_t threads[NUM_THREADS];
	int threadID[NUM_THREADS];

	for (int t=0; t<NUM_THREADS; t++){
		threadID[t] = t;
		int status = pthread_create(&threads[t], NULL, threadFunc, (void *)&threadID[t]);

		if(status){
			printf("Error creating thread %d\n", t);
			exit(-1);
		}
	}

	// WAIT
	for (int t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}

	printf("All threads have completed.\n");
	pthread_exit(NULL);

}

