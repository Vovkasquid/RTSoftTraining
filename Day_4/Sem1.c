#include "bin_sem.h"

#define BUF_SIZE 1048576

int main() {
	char buf[BUF_SIZE];
	int nread;
	int nwrite = 1;
	//int fdin;
	int fdout;
	int shmid;
	const int shared_segment_size = BUF_SIZE + 1;
	char* shared_memory;
	key_t key = ftok("prog1.c", 1);
	key_t keySem = ftok("prog1.1.c", 1);
	key_t keySem1 = ftok("file", 1);
	key_t keySem2 = ftok("file1", 1);
	int semid = binary_semaphore_allocation(keySem, 0666|IPC_CREAT);
	int semid1 = binary_semaphore_allocation(keySem1, 0666|IPC_CREAT);
	int semid2 = binary_semaphore_allocation(keySem2, 0666|IPC_CREAT);

	if (semid <= 0) {
		printf("Unable to gem sem id\n");
		exit(1);
	}	
	shmid = shmget(key, shared_segment_size, 0666| IPC_CREAT);
	if (shmid < 0)
		printf("Shared memory get fail\n");
	shared_memory = shmat(shmid, 0, 0);	
	
	//fdin = open("bin_sem.h", O_RDONLY);
	fdout = open("file.out", O_RDWR|O_CREAT,
			S_IRUSR|S_IWUSR);
	int i = 0;
	sleep(1);
	for (i = 0; i < 100; ++i) {
		printf("iter: %d\n", i++);
		printf("BUF_SIZE+1 = %c\n", shared_memory[BUF_SIZE +1]);
		binary_semaphore_take(semid2);
		printf("Take sem2\n");
		binary_semaphore_take(semid);
		printf("Take sem\n");
		//printf("sem1 shm = %s\n", shared_memory);
		//strncpy(buf, shared_memory, strlen(shared_memory));
		//sleep(2);
		nwrite = write(fdout, shared_memory, BUF_SIZE);
		printf("wrote: %d\nstrlen_mem: %d\n", nwrite, (int)strlen(shared_memory));
		binary_semaphore_free(semid);
		printf("Free sem\n");
		binary_semaphore_free(semid1);
		printf("Free sem1\n");
		//sleep(1);
	}// while (shared_memory[BUF_SIZE + 1] != '1');
	//} while (nwrite == BUF_SIZE);
	/*if (shmdt(shared_memory) == -1)
		printf("shmdt fail\ns");
	if (shmctl(shmid, IPC_RMID, 0) == -1)
		printf("shmctl fail\n");*/
	//binary_semaphore_free(semid);
	close(fdout);
	return 0;
}
