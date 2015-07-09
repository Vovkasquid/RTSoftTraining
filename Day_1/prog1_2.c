#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define size 256
#define big_buf_size 4096
int main() {
	int pid;
	int status;
	int fd[2];
	pid_t pidt;
	
	printf("I`m a parrent %d\n", getpid());
	pipe(fd);
	switch (pid = fork()) {
		case -1:
			printf("Error");
			return -1;
		case 0:
			printf("I`m child and my pid = %d\n", getpid());
			close(fd[0]);
			int ret;
			dup2(fd[1], 1);
			ret = execl("/bin/ls", "ls", "/usr/", "-l", NULL);
			if (ret == -1)
				perror("execvp");
			exit(EXIT_SUCCESS);
	}	
	close(fd[1]);
	char sym[size];
	char buf[big_buf_size];
	int nread;
	
	pidt = wait(&status);
	if (pid == -1)
		perror ("waitpid");
	while ((nread = read(fd[0], sym, size)) > 0) {
		if (nread < size)
			sym[nread] = '\0';
		printf("%s", sym);
		strncat (buf, sym, nread);
	}
	//printf("string after strncat =\n%s\n", buf);
}
