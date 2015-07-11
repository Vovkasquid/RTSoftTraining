#include "bin_sem.h"

#define BUF_SIZE 1048576

int main() {
	int shmid;
	const int shared_segment_size = BUF_SIZE + 1;
	char* shared_memory;
	key_t key = ftok("prog1.c", 1);
	key_t keySem = ftok("tdf", 1);
	key_t keySem1 = ftok("file", 1);
	key_t keySem2 = ftok("rgv", 1);
	
	int semid = binary_semaphore_allocation(keySem, 0666|IPC_CREAT);
	printf("semid: %d\n ",semid);
	int semid1 = binary_semaphore_allocation(keySem1, 0666|IPC_CREAT);
	printf("semid1: %d\n ",semid1);
	int semid2 = binary_semaphore_allocation(keySem2, 0666|IPC_CREAT);
	
	shmid = shmget(key, shared_segment_size, 0666| IPC_CREAT);
	if (shmid < 0)
		printf("Shared memory get fail\n");
	shared_memory = shmat(shmid, 0, 0);
	binary_semaphore_take(semid2);
	printf("%s\n", shared_memory);
	binary_semaphore_free(semid2);
	
	return 0;
}
