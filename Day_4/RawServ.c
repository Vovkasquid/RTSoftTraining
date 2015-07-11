#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

struct headerUDP {
	short src_port;
	short targ_port;
	short length;
	short checksum;
};
int main()
{
	int sock;
	//struct headerUDP header;
	struct sockaddr_in addr;
	char buf[1024];
	int bytes_read;
	
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return 1;
	}
	
	while(1) {
		//bytes_read = recvfrom(sock, buf, sizeof(buf) + sizeof(header), 0, NULL, NULL);
		printf("Wait\n");
		bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
		//buf[bytes_read] = '\0';
		printf("%s\n", buf);
	}
	return 0;
}
