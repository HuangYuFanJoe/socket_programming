#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("Can't allocate sockfd");
		exit(1);
	}

	struct sockaddr_in clientaddr, serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(8080);

	bind(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr));
	listen(sockfd, 7878);

	socklen_t addrlen = sizeof(clientaddr);
	int count = 1;
	char data[50] = {};
	while(1){  // receive data
		int connfd = accept(sockfd, (struct sockaddr *) &clientaddr, &addrlen);
		recv(connfd, data, 50, 0);
		printf("%s \n", data);
	        close(connfd);
	}

	return 0;
}
