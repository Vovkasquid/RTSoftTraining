#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *print_hello(void *num) {
	long t_num;
	t_num = (long) num;
	pthread_t in;
	int i;	
	in = pthread_self();
	for (i = 0; i < 10; ++i) {
		printf("Hello World! Thread ind: %ld , Thread num %ld\n", in, t_num);
		sleep(1);
	}
}

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for (t = 0; t < NUM_THREADS; ++t) {
		printf("In main: creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
		if (rc) {
			printf("Error; return code is %d\n", rc);
		}
	}
	
	for (t = 0; t < NUM_THREADS; ++t) {
	pthread_join(threads[t], NULL);
	printf("Thread #%ld finished \n", t);
	}

	return 0;
}
