// server program for udp connection
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../inc/servidor.h"

//#define PORT 2002
#define MAXLINE 1000
  
// Driver code
void servidor_UDP(int PORT)
{   
    char buffer[100];
    char * bufferito = 0;
    long length;
    int listenfd, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    system("clear");
    printf("Esperando conexion\n");
  
    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);        
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET; 
   
    // bind server address to socket descriptor
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
       
    //receive the datagram
    len = sizeof(cliaddr);
    int n = recvfrom(listenfd, buffer, sizeof(buffer),
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server
    buffer[n] = '\0';
    
    printf("\nComando buscado: %s\n",buffer);

    //run find command and save results in a file
    strcat(buffer," > resultado.txt");
    system(buffer);

    // retrive results from file and copy them in a string
    FILE * f = fopen ("resultado.txt", "rb");
    if (f)
    {
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

    // send the response
    sendto(listenfd, bufferito, MAXLINE, 0,
          (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    printf("\nRESULTADOS\n%s\n\n",bufferito);
    printf("Resultados enviados\n");
    remove("resultado.txt");
    exit(1);
}