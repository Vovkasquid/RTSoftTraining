#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	char message[] = "Hello World!\n";
	char buf[sizeof(message)];
	int sock;
	struct sockaddr_in addr;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect");
		return 1;
	}
	
	send(sock, message, sizeof(message), 0);
	recv(sock, buf, sizeof(message), 0);
	printf("Receive from Server: %s\n", buf);
	close(sock);
	
	return 0;
}
