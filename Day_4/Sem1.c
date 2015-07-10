#include "bin_sem.h"

#define BUF_SIZE 1048576

int main() {
	char buf[BUF_SIZE];
	int nread;
	int nwrite;
	//int fdin;
	int fdout;
	int shmid;
	const int shared_segment_size = 1048576;
	char* shared_memory;
	key_t key = ftok("prog1.c", 1);
	shmid = shmget(key, shared_segment_size, 0666| IPC_CREAT);
	if (shmid < 0)
		printf("Shared memory get fail\n");
	shared_memory = shmat(shmid, 0, 0);	
	
	//fdin = open("bin_sem.h", O_RDONLY);
	fdout = open("file1", O_RDWR|O_CREAT,
			S_IRUSR|S_IWUSR);
	sleep(1);
	do { 
		nwrite = write(fdout, shared_memory, ((int)strlen(shared_memory)));
	
	} while (nwrite == BUF_SIZE);
	return 0;
}
