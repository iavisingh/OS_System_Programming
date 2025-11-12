#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define BIND_PORT (4060U)
#define BUFFER_SIZE (1024U)

void main()
{
	int ret,listen_sock, client_sock;
	struct sockaddr_in6 bind_addr, client_addr;
	fd_set read_fd;
	char buffer[BUFFER_SIZE];
	socklen_t addrlen;
	struct timeval timeout;
	
	printf("Server application -->>\n");

	listen_sock = socket(AF_INET6, SOCK_STREAM, 0);
	if(listen_sock == -1) {
		perror("socket create failure\n");
		exit(EXIT_FAILURE);
	}
	printf("sock: %d\n",listen_sock);

	bind_addr.sin6_port = htons(BIND_PORT);
	bind_addr.sin6_family = AF_INET6;
	bind_addr.sin6_addr = (in6addr_any);
	//bind_addr.sin6_scope_id = 
	
	ret = bind(listen_sock, (const struct sockaddr *)&bind_addr, (socklen_t) sizeof(bind_addr));
	if(ret == -1) {
		perror("socket bind failure\n");
		close(listen_sock);
		exit(EXIT_FAILURE);
	}
	printf("sock: %d, bind: %d\n",listen_sock, ret);

	ret = listen(listen_sock, 0);
	if(ret == -1) {
		perror("socket listen failure\n");
		close(listen_sock);
		exit(EXIT_FAILURE);
	}
	printf("sock: %d, listen: %d\n",listen_sock, ret);

	do {
		client_sock = accept(listen_sock, (struct sockaddr *) &client_addr, &addrlen);
		if(client_sock == -1) {	
			perror("socket accept failure\n");
			close(listen_sock);
			exit(EXIT_FAILURE);
		}
		printf("connection accepted\n");
		do {

			FD_CLR(client_sock, &read_fd);
			FD_SET(client_sock, &read_fd);

			timeout.tv_sec = 1;
			timeout.tv_usec = 0;

			ret = select(client_sock + 1, &read_fd, NULL, NULL, &timeout);
			if(ret == 1) {
				if(FD_ISSET(client_sock,&read_fd)) {
				//sock event ready for rx
					ret = recv(client_sock, buffer, BUFFER_SIZE, 0);
				
					if((ret > 0) && (ret <= BUFFER_SIZE)) {	
						printf("socket receive: %d bytes, %*s\n",ret, ret,buffer);
					} else if(ret == 0) {
						printf("socket gracefully disconnected\n");
						close(client_sock);
						break;
					} else {
						printf("socket receive err\n");
						close(client_sock);
						break;
					}
				}	
			} else if (ret == 0) {
				printf("select timeout\n");
				//timeout no data received;
			} else {
				//socket err
				perror("socket select error\n");
				close(client_sock);
				break;
			}
		} while(1);
	} while(1);
}


