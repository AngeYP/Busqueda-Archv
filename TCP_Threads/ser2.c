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
//#include "header/fserver.h"

#define MAX 1000
// #define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void funfserver(int * sockfd)
{
	char buff[MAX];
	int n;
	char * bufferito = 0;
    long length;

	// infinite loop for chat
	for (;;) {
		printf("Presione ENTER para continuar\n");
		getchar();
		system("clear");
		printf("Esperando mensaje\n");

		bzero(buff, MAX);
		// read the message from client and copy it in buffer
		read(*sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("\nCerrando servidor...\n");
            break;
        } else {
        	printf("\nComando a consultar: %s\n", buff);

			buff[strcspn(buff, "\n")] = 0;
		    strcat(buff," > resultado.txt");
		    system(buff);

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
	        buff[strlen(buff)-3] = 0;

	        write(*sockfd, buff, sizeof(buff));

	        printf("RESULTADOS:\n%s\n",buff);
    		printf("Resultados enviados\n\n");
        }
	}
}

// Driver function
void fserver_TCP(int PORT)
{
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

  pthread_create(&tid, NULL, (void *) funfserver, &connfd);
  pthread_join(tid,NULL);
  sleep(1);
	// if((childpid = fork()) == 0){
	// 	close(sockfd);// Function for chatting between client and server
	// 	funfserver(&connfd);
	// }
  //
	// 	// After chatting close the socket
	close(sockfd);
  pthread_exit(NULL);
	// if (childpid!=0)
	// {
	// 	wait(NULL);
	// }
	// if (childpid!=0)
	// {
	// 	return;
	// }
}

int main(){
  fserver_TCP(2020);
}
