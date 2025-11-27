#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 4060
#define BACKLOG 0
#define SERVER_IP4_ADDRESS "127.0.0.1"

void fflush_stdin()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void main() 
{
	int client_sock, ret;
	struct sockaddr_in server_addr;
	socklen_t addrlen;

	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(client_sock < 0) {
		perror("socket create err:\n");
		exit(-1);
	}

	printf("socket ipv4: %d\n", client_sock);
	
	server_addr.sin_port = ntohs(SERVER_PORT);
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, SERVER_IP4_ADDRESS, (void *) &server_addr.sin_addr);

	ret = connect(client_sock, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
	if(ret < 0) {
		perror("connect err\n");
		close(client_sock);
		exit(-2);
	}

	printf("client_sock: %d, connect success\n", client_sock);
	
	while(1) {
		
		char sendbuffer[1024] = {0};
		printf("===>>");
		fflush(stdout);
		scanf("%[^\n]", sendbuffer);
		fflush_stdin();
		ret = send(client_sock, (const void *)sendbuffer, strlen(sendbuffer), 0);
		if(ret < 0) {
			perror("send err");
			close(client_sock);
			exit(-3);
		}else {
			printf("client sock: %d, sent: %d, %s\n", client_sock, ret, sendbuffer);
		}
		char rcvbuffer[1024] = {0};
		ret = recv(client_sock, (void *)rcvbuffer, sizeof(rcvbuffer), 0);
		if(ret < 0) {
			perror("recv err");
			close(client_sock);
			exit(-4);
		} else if (ret == 0) {
			printf("connection closed from server\n");
			close(client_sock);
			exit(-5);
		} else {
			printf("client sock: %d, recv:%d bytes, %s\n", client_sock, ret, rcvbuffer);
		}
	}
}


