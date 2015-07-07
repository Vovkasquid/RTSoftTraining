#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	int pid;
	int fd[2];
	
	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	//write(fd[1],"data\n", 10);
	switch(pid = fork()) {
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			close(fd[0]);
			char sym[1024];
			int ret;
			dup2(fd[1], 1);
			ret = execl("/bin/ls", "ls", "/tmp/", "-l", NULL);
			if (ret == -1)
				perror("execvp");
			exit(EXIT_SUCCESS);
			//printf("sym = %s \n", sym);
			//return 0;
	}
	close(fd[1]);
	char sym[1024];
	read(fd[0], sym, 1024);
	printf("%s \n", sym);
	//printf("!!!!!!!!!!!!!!22222222222222233333333333333333\n");
}
