#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

char password[256];

void *WritingThread() {
	printf("Enter password\n");
	scanf("%s", password);
}

void *VerifyPassword(void* pass) {
	char *passw;
	passw = (char*) pass;
	printf("test char = %s\n",passw);
}
		

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	char pass[256] = "ABCD";
	printf("In main: creating thread 1\n");
	rc = pthread_create(&threads[0], NULL, WritingThread, NULL);
	if (rc) {
		printf("Error; return code is %d\n", rc);
	}

	printf("In main: creating thread 2\n");
	rc = pthread_create(&threads[1], NULL, VerifyPassword, (void *) pass);
	if (rc) {
		printf("Error; return code is %d\n", rc);
	}
	
	
	for (t = 0; t < NUM_THREADS; ++t) {
		pthread_join(threads[t], NULL);
		printf("Thread #%ld finished \n", t);
	}

	return 0;
}
