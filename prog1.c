#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;
	int fd[2];
	
	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	//close(fd[1]);
	write(fd[0],"data", 10);
	switch(pid = fork()){
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			//close(fd[0]);
			char sym;
			read(fd[1], sym, 1);
			printf("sym = %c", sym);
			return 0;
	}
}
