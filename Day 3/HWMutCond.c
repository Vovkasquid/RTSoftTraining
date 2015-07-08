#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  3

pthread_mutex_t mutex;
pthread_cond_t сond;

void * 
