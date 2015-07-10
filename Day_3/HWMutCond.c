#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  10

int global_i = 1;
int global_j = NUM_THREADS;
pthread_mutex_t mutex;
pthread_mutex_t fict;
pthread_cond_t blocked;

void *ThreadsUseIt(void* num) {
	int i;
	long t;
	
	t = (long) num;
	pthread_mutex_lock(&mutex);
	i = global_i;
	global_i++;
	pthread_mutex_unlock(&mutex);
	printf("I`m thread %ld, I`m sleeping for %d second \n", t, i);
	sleep(i);
	printf("Thread %ld woke up\n", t);
	pthread_mutex_lock(&fict);
	global_j --;
	if (!global_j)
		pthread_cond_broadcast(&blocked);
	else {
		printf("Thread %ld wait\n", t);
		pthread_cond_wait(&blocked, &fict);
	}
	printf("Thread %ld perfomed all works\n", t);
	pthread_mutex_unlock(&fict);
	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	int i;
	long t = 1;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&fict, NULL);
	pthread_cond_init (&blocked, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_create(&threads[i], &attr, ThreadsUseIt, (void *) t);
		printf("Thread %ld started\n", t);
		++t;
	}
	
	/*Wait*/
	for (i = 0; i < NUM_THREADS; ++i)
		pthread_join(threads[i], NULL);
	printf("All threads finished\n");
	
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&fict);
  	pthread_cond_destroy(&blocked);
  	pthread_exit(NULL);
}
