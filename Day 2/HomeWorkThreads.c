//Correct password - ABCD

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

pthread_t threads[NUM_THREADS];
char password[256];

void *WritingThread() {
	printf("Enter password\n");
	scanf("%s", password);
}

void *VerifyPassword(void* pass) {	
	char *passw;
	passw = (char*) pass;
	pthread_join(threads[0], NULL);
	if(!strcmp(passw, password))
		printf("The password is confirmed\n");
	else 
		printf("Incorrect password\n");
}
		

int main (int argc, char *argv[]) {
	int rc;
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
	pthread_join(threads[1], NULL);
	printf("Thread 1 finished\n");
	return 0;
}
