#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

struct headerUDP {
	short src_port;
	short targ_port;
	short length;
	short checksum;
};

int main() {
	char msg1[] = "MESSAGE1";
	char msg2[20];
	int sock;
	struct sockaddr_in addr;
	struct headerUDP header;
	
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (sock < 0) {
		perror("socket");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	//addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	//header.src_port = htons(3425);
	header.targ_port = htons(3425);
	header.checksum = 0;
	header.length = sizeof(header) + sizeof(msg1);
	memcpy((void *)msg2, (const void *)&header, sizeof(header));
    	memcpy((void *)(msg2 + sizeof(header)), (void *) msg1, sizeof(msg1));
	sendto(sock, msg1, sizeof(msg1) + sizeof(header), 0, (struct sockaddr *)&addr, sizeof(addr));
	printf("send \n");
	
	close(sock);
	return 0;
}
