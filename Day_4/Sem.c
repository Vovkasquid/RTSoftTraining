#include "bin_sem.h"

#define BUF_SIZE 1048576
int main() {
	char buf[BUF_SIZE];
	int nread;
	int nwrite;
	int fdin;
	int fdout;
	
	fdin = open("100mb_file", O_RDONLY);
	fdout = open("100mb_file1", O_RDWR|O_CREAT,
			S_IRUSR|S_IWUSR);
	while ((nread = read(fdin, buf, BUF_SIZE)) > 0) {
		//if (nread < BUF_SIZE)
			//buf[nread] = '\0'
		nwrite = write(fdout, buf, nread);
	}
	return 0;
}
