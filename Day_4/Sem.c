#include "bin_sem.h"

#define BUF_SIZE 1048576

int main() {
	char buf[BUF_SIZE];
	int nread;
	int flag = 0; 
	int nwrite;
	int fdin,fdout;
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
	printf("semid2: %d\n ",semid2);
	
	binary_semaphore_initialize(semid);
	binary_semaphore_initialize(semid1);
	binary_semaphore_initialize_0(semid2);
	
	shmid = shmget(key, shared_segment_size, 0666| IPC_CREAT);
	if (shmid < 0)
		printf("Shared memory get fail\n");
	shared_memory = shmat(shmid, 0, 0);
	shared_memory = "4555";
	shared_memory[4] = '\0';
	binary_semaphore_free(semid2);
	sleep(10);
	binary_semaphore_deallocate(semid);
	binary_semaphore_deallocate(semid1);
	binary_semaphore_deallocate(semid2);
	return 0;
	shared_memory[BUF_SIZE+1] = '0';
	
	fdin = open("100mb_file", O_RDONLY);
	//fdout = open("file.out", O_RDWR|O_CREAT,
			//S_IRUSR|S_IWUSR);
			int i = 0;
	while ((nread = read(fdin, buf, BUF_SIZE)) > 0) {
		printf("nread after while: %d\n", nread);
		binary_semaphore_take(semid1);
		printf("Take sem1\n");
		binary_semaphore_take(semid);
		printf("Take sem\n");
		printf("iter: %d\n", i++);
		if (nread < BUF_SIZE) {
			buf[nread] = '\0';
			//printf("buf last sem = %s \n", buf);
			//shared_memory[BUF_SIZE+1] = '1';
		}
		//write(fdout, buf, BUF_SIZE);
		printf("BUF_SIZE+1 = %c\n", shared_memory[BUF_SIZE +1]);
		printf("read: %d\n", nread);
		strcpy(shared_memory, buf);
		//sleep(5);
		binary_semaphore_free(semid);
		printf("Free sem\n");
		binary_semaphore_free(semid2);
		printf("Free sem2\n");
		//if (flag)
			//shared_memory[0] = '\0';
	}
	sleep(2);
	if (shmdt(shared_memory) == -1)
		printf("shmdt fail\n");
	else 
		printf("shmdt success\n");
	if (shmctl(shmid, IPC_RMID, 0) == -1)
		printf("shmctl fail\n");
	else 
		printf("shmctl success\n");
	binary_semaphore_deallocate(semid);
	binary_semaphore_deallocate(semid1);
	binary_semaphore_deallocate(semid2);
	close(fdin);
	//close(fdout);
	return 0;
}
