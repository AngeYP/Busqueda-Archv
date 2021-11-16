// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
  
#define PORT 5000
#define MAXLINE 1000
#define MAXFIND 500
  
// Driver code
int main()
{   
    char buffer[100];
    char *finddata = malloc(MAXFIND);
    int sockfd, n;
    struct sockaddr_in servaddr;

    printf("Introduzca el comando find con su informacion\n");
    fgets(finddata, MAXFIND, stdin);

    if ((strlen(finddata) > 0) && (finddata[strlen (finddata) - 1] == '\n'))
        finddata[strlen (finddata) - 1] = '\0';

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
    printf("\nRESULTADOS: \n%s",buffer);
  
    // close the descriptor
    close(sockfd);
}