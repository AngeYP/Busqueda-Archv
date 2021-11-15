// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT     8080
#define MAXLINE 1024
   
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
   

    char *datafile, name[255], directorio[1000];
    int option;

    printf("Insertar el tipo de busqueda\n");
    scanf("%i",&option);

    printf("Insertar el dato a buscar\n");
    scanf("%s",name);

    printf("Insertar el directorio\n");
    scanf("%s",directorio);

    datafile = (char*)malloc((strlen(name)+strlen(directorio)+2) * sizeof(char));

    sprintf(datafile, "%i",option);
    strcat(datafile,"^");
    strcat(datafile,name);
    strcat(datafile,"?");
    strcat(datafile,directorio);

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n, len;
       
    sendto(sockfd, (const char *)datafile, strlen(datafile),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Hello message sent.\n");
           
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    free(datafile);
   
    close(sockfd);
    return 0;
}