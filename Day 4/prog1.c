#include "bin_sem.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	key_t key = ftok("File1.c", 1);
	int semid = binary_semaphore_allocation(key, 0666 
					| IPC_CREAT);
	binary_semaphore_initialize(semid);
	binary_semaphore_take(semid);
	printf("pr1: proc1 took the semaphore\n");
	sleep(20);
	binary_semaphore_free(semid);
	printf("pr1: proc1 release the semaphore\n");
	exit(0);
}
