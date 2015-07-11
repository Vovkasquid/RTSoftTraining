//Correct password - ABCD

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

int result = 0;
pthread_mutex_t mutex;
pthread_mutex_t fict;
pthread_mutex_t write;
pthread_cond_t blocked;
char password[256];

void *WritingThread() {
	while(1) {
		pthread_mutex_lock(&write);
		if (result)
			break;
		pthread_mutex_lock(&mutex);
		printf("Enter password\n");
		scanf("%s", password);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&fict);
	}
}

void *VerifyPassword(void* pass) {	
	char *passw;
	while(!result) {
		pthread_mutex_lock(&fict);
		pthread_mutex_lock(&mutex);
		passw = (char*) pass;
		pthread_mutex_unlock(&mutex);
		if(!strcmp(passw, password)) {
			printf("The password is confirmed\n");
			result++;
			pthread_mutex_unlock(&write);
			break;
		} else {
			printf("Incorrect password, try again\n");
		}
		pthread_mutex_unlock(&write);
	}
}
		

int main (int argc, char *argv[]) {
	pthread_mutex_lock(&fict);
	int rc;
	char pass[256] = "ABCD";
	pthread_t threads[NUM_THREADS];
	printf("In main: creating thread 1\n");
	rc = pthread_create(&threads[0], NULL, WritingThread, NULL);
	if (rc) {
		printf("Error 1 thread; return code is %d\n", rc);
	}

	printf("In main: creating thread 2\n");
	rc = pthread_create(&threads[1], NULL, VerifyPassword, (void *) pass);
	if (rc) {
		printf("Error 2 thread; return code is %d\n", rc);
	}
	pthread_join(threads[1], NULL);
	printf("Thread 1 finished\n");
	pthread_join(threads[0], NULL);
	printf("Thread 0 finished\n");
	return 0;
}
