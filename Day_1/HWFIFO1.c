#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int ret;
	int fd;
	/*if(mknod("MY_FIFO", S_IFIFO | 0666, 0) < 0) {
		printf("Can't create MY_FIFO\n");
 		exit(-1); 
 	}*/
 	if ((fd = open("MY_FIFO", O_WRONLY)) < 0) {
		printf("Can\'t open MY_FIFO for writing\n");
		//exit(-1); 
	}
	dup2(fd, 1);
	ret = execl("/bin/ls", "ls", "/usr/", "-l", NULL);
	if (ret == -1)
		perror("execvp");
	return 0;
}	
