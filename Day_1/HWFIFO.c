#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define size 256
#define big_buf_size 4096

int main()
{	
	int nread;
	int fd;
	char sym[size];
	//unlink("MY_FIFO");
	if(mknod("MY_FIFO", S_IFIFO | 0666, 0) < 0) {
		printf("Can\'t create MY_FIFO\n");
 		exit(-1);
 	}
 	if ((fd = open("MY_FIFO", O_RDONLY)) < 0) {
		printf("Can\'t open MY_FIFO for writing\n");
		exit(-1); 
	}
	while ((nread = read(fd, sym, size)) > 0) {
		if (nread < size)
			sym[nread] = '\0';
		printf("%s", sym);
	}
	unlink("MY_FIFO");
}
