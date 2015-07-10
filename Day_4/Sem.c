#include "bin_sem.h"

#define BUF_SIZE 1048577

int main() {
	char buf[BUF_SIZE];
	int nread;
	int flag = 0; 
	int nwrite;
	int fdin,fdout;
	int shmid;
	const int shared_segment_size = 1048578;
	char* shared_memory;
	key_t key = ftok("prog1.c", 1);
	key_t keySem = ftok("prog1.1.c", 1);
	key_t keySem1 = ftok("file", 1);
	key_t keySem2 = ftok("file1", 1);
	int semid = binary_semaphore_allocation(keySem, 0666|IPC_CREAT);
	int semid1 = binary_semaphore_allocation(keySem1, 0666|IPC_CREAT);
	int semid2 = binary_semaphore_allocation(keySem2, 0666|IPC_CREAT);
	
	binary_semaphore_initialize(semid);
	binary_semaphore_initialize(semid1);
	binary_semaphore_initialize(semid2);
	
	//binary_semaphore_take(semid2);
	
	shmid = shmget(key, shared_segment_size, 0666| IPC_CREAT);
	if (shmid < 0)
		printf("Shared memory get fail\n");
	shared_memory = shmat(shmid, 0, 0);
	shared_memory[BUF_SIZE+1] = '0';
	
	fdin = open("bin_sem.c", O_RDONLY);
	//fdout = open("file.out", O_RDWR|O_CREAT,
			//S_IRUSR|S_IWUSR);
	while ((nread = read(fdin, buf, BUF_SIZE)) > 0) {
		binary_semaphore_take(semid1);
		binary_semaphore_take(semid);
		if (nread < BUF_SIZE) {
			buf[nread] = '\0';
			//printf("buf last sem = %s \n", buf);
			shared_memory[BUF_SIZE+1] = '1';
		}
		//write(fdout, buf, BUF_SIZE);
		printf("BUF_SIZE+1 = %c\n", shared_memory[BUF_SIZE +1]);
		printf("read: %d\n", nread);
		strcpy(shared_memory, buf);
		//sleep(5);
		binary_semaphore_free(semid);
		binary_semaphore_free(semid2);
		//if (flag)
			//shared_memory[0] = '\0';
	}
	sleep(5);
	if (shmdt(shared_memory) == -1)
		printf("shmdt fail\n");
	if (shmctl(shmid, IPC_RMID, 0) == -1)
		printf("shmctl fail\n");
	binary_semaphore_deallocate(semid);
	binary_semaphore_deallocate(semid1);
	binary_semaphore_deallocate(semid2);
	close(fdin);
	//close(fdout);
	return 0;
}
