#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void serv_chat(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, MAX);
		if(read(sockfd, buff, sizeof(buff))==-1){
			printf("Read failed...\n");
			exit(0);
		}
		printf("Message from client: %s\n", buff);
		bzero(buff, MAX);
		printf("Enter message to client: ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
		buff[n]='\0';
		if(write(sockfd, buff, sizeof(buff))==-1){
			printf("Write failed...\n");
			exit(0);
		}
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

int main(){
	int sockfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else{
		printf("Socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else{
		printf("Socket successfully binded..\n");
	}
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else{
		printf("Server listening..\n");
	}
	len = sizeof(cli);
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}
	else{
		printf("server acccept the client...\n");
	}
	serv_chat(connfd);
	close(sockfd);
}


