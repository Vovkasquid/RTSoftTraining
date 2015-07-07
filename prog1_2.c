#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define size 1024
int main() {
	int pid;
	int fd[2];
	
	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	switch(pid = fork()) {
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			close(fd[0]);
			int ret;
			dup2(fd[1], 1);
			ret = execl("/bin/ls", "ls", "/tmp/", "-l", NULL);
			if (ret == -1)
				perror("execvp");
			exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	char sym[size];
	//int nread;
	//while ((nread = read(fd[0], sym, size)) > 0)
	read(fd[0], sym, size);
	printf("%s\n", sym);
}
