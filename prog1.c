#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;
	int fd[2];
	
	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	write(fd[1],"data\n", 10);
	switch(pid = fork()){
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			close(fd[1]);
			char sym[10];
			read(fd[0], sym, 10);
			printf("sym = %s \n", sym);
			return 0;
	}
	close(fd[0]);
}
