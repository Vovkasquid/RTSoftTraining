#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
int change = 30;

/*void *print_hello(void *num) {
	long t_num;
	t_num = (long) num;
	pthread_t in;
	int i;	
	in = pthread_self();
	for (i = 0; i < 10; ++i) {
		printf("Hello World! Thread ind: %ld , Thread num %ld\n", in, t_num);
		sleep(1);
	}
}*/

void *plus_thread() {
	int i = 0;
	for (i = 0; i < 10; i++) {
		change++;
		printf("change plus = %d\n", change);
		sleep(1);
	}
}
	
void *minus_thread() {
	int i;
	for (i = 0; i < 10; i++) {
		change--;
		printf("change minus = %d\n", change);
		sleep(1);
	}
}
int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	//long change = 30;
	//for (t = 0; t < NUM_THREADS; ++t) {
	printf("In main: creating thread %ld\n", t);
	rc = pthread_create(&threads[0], NULL, plus_thread, NULL);
	if (rc) {
		printf("Error; return code is %d\n", rc);
	}
	rc = pthread_create(&threads[1], NULL, minus_thread, NULL);
	if (rc) {
		printf("Error; return code is %d\n", rc);
	}
	//}
	
	for (t = 0; t < NUM_THREADS; ++t) {
		pthread_join(threads[t], NULL);
		printf("Thread #%ld finished \n", t);
	}

	return 0;
}
