#include <stdio.h>
#include <unistd.h>

#define buf_size 256

int main() {
	int pid;
	int fd[2];
	int nread;
	int nwrite;
	char buf[buf_size];

	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	//write(1, "Input something \n", buf_size);
	printf("Input something \n");
	scanf("%s", buf);
	//nread = read(0, buf, buf_size);
	write(fd[1], buf, buf_size);
	switch(pid = fork()) {
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			close(fd[1]);
			char sym[nread];
			read(fd[0], sym, nread);
			printf("sym = %s \n", sym);
			return 0;
	}
	close(fd[0]);
}
