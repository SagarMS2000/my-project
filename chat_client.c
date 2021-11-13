#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void client_chat(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the message : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
		if(write(sockfd, buff, sizeof(buff))==-1){
			printf("Write failed...\n");
			exit(0);
		}
		bzero(buff, sizeof(buff));
		if(read(sockfd, buff, sizeof(buff))==-1){
			printf("Read failed...\n");
			exit(0);
		}
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else{
		printf("Socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("10.20.100.119");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else{
		printf("connected to the server..\n");
	}
	client_chat(sockfd);
	close(sockfd);
}


