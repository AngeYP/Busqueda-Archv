// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include "header/cliente.h"
  
//#define PORT 2002
#define MAXLINE 1000
#define MAXFIND 500
  
// Driver code
void cliente_UDP(int PORT) {

    system("clear");

    char buffer[100];
    char *finddata = malloc(MAXFIND);
    int sockfd, n;
    struct sockaddr_in servaddr;
    int option = 0;

    do {
        printf("Elegir una opcion:\n1. Comenzar una busqueda\n2. Recibir ayudar\n3. Salir\nIntroduzca el numero: ");
        scanf("%i",&option);
        system("clear");
        switch(option) {
            case 1: askfind(finddata);
            break;
            case 2: system("man find");
            break;
            case 3: return; 
        }
        system("clear");
    } while (option!=1);

    char *ip = malloc(15);
    askipadress(ip);


    if ((strlen(finddata) > 0) && (finddata[strlen (finddata) - 1] == '\n'))
        finddata[strlen (finddata) - 1] = '\0';

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
      
    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      
    // connect to server

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }
  
    // request to send datagram
    // no need to specify server address in sendto
    // connect stores the peers IP and port
    sendto(sockfd, finddata, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
      
    // waiting for response
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    system("clear");
    printf("RESULTADOS DEL SERVIDOR %s \n%s",ip,buffer);
    printf("\nPor favor, presiones ENTER para continuar\n");
    getchar();
  
    // close the descriptor
    close(sockfd);
}

void askfind(char * finddata) {
    getchar();
    printf("Introduzca el comando find con su informacion\n");
    fgets(finddata, MAXFIND, stdin);
}

void askipadress(char * ip) {
    system("clear");
    printf("Introduzca la direccion IP del servidor\n");
    fgets(ip,15,stdin);
}