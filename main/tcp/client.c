#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "header/client.h"

#define MAX 1000
// #define PORT 8080
#define SA struct sockaddr

void funcliente(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		printf("Presione ENTER para continuar\n");
		getchar();
		system("clear");
		printf("Introduzca su comando find o exit para salir: \n");
		bzero(buff, sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("\nCerrando cliente...\n");
			break;
		} else {
			bzero(buff, sizeof(buff));
			read(sockfd, buff, sizeof(buff));
			printf("\nRESULTADOS: \n%s\n", buff);
		}
	}
}

void cliente_TCP(int PORT)
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	char *ip = malloc(15);
    askipaddress(ip);

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	funcliente(sockfd);

	// close the socket
	close(sockfd);
}

void askipaddress(char * data) {

  	puts("\nIntroduzca la direccion IP");
	scanf("%s",data);
	if ((strlen(data) > 0) && (data[strlen (data) - 1] == '\n'))
                data[strlen (data) - 1] = '\0';
}
