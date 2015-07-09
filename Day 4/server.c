#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

int main()
{
	int sock, listener;
	struct sockaddr_un addr;
	char buf[1024];
	int bytes_read;
	
	listener = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listener < 0) {
		perror("socket");
		return 1;
	}
	
	addr.sun_family = AF_UNIX;
	//addr.sin_port = htons(3425);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	unlink("server_socket");
	strcpy(addr.sun_path, "server_socket");
	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return 1;
	}
	
	listen(listener, 1);
	while(1) {
		sock = accept(listener, NULL, NULL);
		if (sock < 0) {
			perror("accept");
			return 1;
		}
		
		while(1) {
			bytes_read = recv(sock, buf, 1024, 0);
			if (bytes_read <= 0) {
				break;
			}
			printf("Receive message: %s\n", buf);
			send(sock, buf, bytes_read, 0);
		}
		close(sock);
	}
	return 0;
}
