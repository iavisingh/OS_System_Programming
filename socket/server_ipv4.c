#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BIND_PORT 4060
#define BACKLOG 0
void main() 
{
	int list_sock, client_sock, ret, opt;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr = {0};
	socklen_t addrlen;

	list_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(list_sock < 0) {
		perror("socket create err:\n");
		exit(-1);
	}
	
	opt = 1;
	setsockopt(list_sock, SOL_SOCKET, SO_REUSEADDR, 
			(const char *) &opt, sizeof(int));

	printf("socket ipv4: %d\n", list_sock);
	
	server_addr.sin_port = ntohs(BIND_PORT);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(list_sock, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
	if(ret < 0) {
		perror("bind err\n");
		close(list_sock);
		exit(-2);
	}

	printf("list_sock: %d, bind success\n", list_sock);

	ret = listen(list_sock, BACKLOG);
	if(ret < 0) {
		perror("listen err\n");
		close(list_sock);
		exit(-3);
	}

	printf("list_sock: %d, BACKLOG: %d\n", list_sock, BACKLOG);
	
	printf("server now running ======>>>\n");
	while(1) {
		
		printf("server listening for incoming connections !!!\n");
		addrlen = sizeof(client_addr);
		client_sock = accept(list_sock, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen);
		if(client_sock < 0) {
			perror("accept err:\n");
			close(list_sock);
			exit(-4);
		}
		
		printf("listen sock: %d, received connection, client_sock: %d\n", list_sock, client_sock);

		while(1) {
			char rcvbuffer[1024] = {0};
			ret = recv(client_sock, (void *)rcvbuffer, sizeof(rcvbuffer), 0);
			if(ret < 0) {

				perror("recv err");
				close(client_sock);
				break;

			} else if (ret == 0) {

				printf("connection closed from peer\n");
				close(client_sock);
				break;

			} else {

				printf("client sock: %d, recv:%d bytes, %s\n", client_sock, ret, rcvbuffer);

			}
			
 			//ECHO BACK			
			ret = send(client_sock, (const void *)rcvbuffer, strlen(rcvbuffer), 0);
			if(ret < 0) {
				perror("send err");
				close(client_sock);
				break;
			} else {
				printf("client sock: %d, send: %d bytes, %s\n", client_sock, ret, rcvbuffer);
			}


		}
	}
}


