#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "header/tserver.h"

#define MAX 1000
#define SA struct sockaddr

// Function designed for chat between client and server.
void funtserver(int * sockfd)
{
	char buff[MAX];
	int n;
	char * bufferito = 0;
    long length;

	// infinite loop for chat
	system("clear");
	printf("Esperando mensaje\n");

	bzero(buff, MAX);
	// read the message from client and copy it in buffer
	read(*sockfd, buff, sizeof(buff));

    // if msg contains "Exit" then server exit and chat ended.
	printf("\nComando a consultar: %s\n", buff);

	//run find command and save results in a file
	buff[strcspn(buff, "\n")] = 0;
    strcat(buff," > resultado.txt");
    system(buff);

    // retrive results from file and copy them in a string
    FILE * f = fopen ("resultado.txt", "rb");
    if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		bufferito = malloc (length);
		if (bufferito)
		{
			fread (bufferito, 1, length, f);
		}
		fclose (f);
    }

    bzero(buff, MAX);
    n = 0;
    strcpy(buff, bufferito);

    //send the response
    write(*sockfd, buff, sizeof(buff));

    printf("RESULTADOS:\n%s\n",buff);
	printf("Resultados enviados\n\n");
	remove("resultado.txt");
	printf("Presione ENTER para continuar\n");
	getchar();
	system("clear");

	exit(1);
}

// Driver function
void tserver_TCP(int PORT)
{
	system("clear");
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	pid_t childpid;
  	pthread_t tid;
	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Creacion de socket fallida...\n");
		exit(0);
	}
	else
		printf("Creacion de socket exitosa..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Conexion de socket fallida...\n");
		exit(0);
	}
	else
		printf("Conexion de socket exitosa..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);

	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	//thread function to receive, search and send information
	pthread_create(&tid, NULL, (void *) funtserver, &connfd);
	pthread_join(tid,NULL);
	sleep(1);

	close(sockfd);
	pthread_exit(NULL);

}
