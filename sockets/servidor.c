// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

void cleanbuffer(char *str) {
	int i = 0, j = 0;
	while (str[i]) {
		if (str[i] > 32 && str[i] < 126) {
			printf("Hola");
		}
		else {
			str[j++] = str[i];
		}
		i++;
	}
	str[j]=0;
}

// void RemoveChars(char *s, char c)
// {
//     int writer = 0, reader = 0;

//     while (s[reader])
//     {
//         if (s[reader]!=c) 
//         {   
//             s[writer++] = s[reader];
//         }

//         reader++;       
//     }

//     s[writer]=0;
// }

int legth(char *str) {
	int i = 0;
	while (str[i]) {
		if (str[i] == '?') {
			return i;
		}
		i++;
	}
	return 0;
}

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	char type[1];
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt

//**********************************AQUI******************************************//
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';

	char *temp;
	strcat(temp,buffer);
	// cleanbuffer(temp);

	// printf("[%s]\n",temp);
	temp+=4;

	strncat(type, temp, 1);
	char *file = temp+2;

	int i = legth(temp);
	
	char *directory = file+(i);
	
	file[i-2]='\0';


	printf("\n%s\n",type);
	printf("%s\n",file);
	printf("%s\n",directory);


	// strncat(type, buffer, 1);
	// char *file = buffer+2;

	// int i = legth(file);
	
	// char *directory = buffer+(i+2);
	
	// file[i]='\0';


	// printf("\n%s\n",type);
	// printf("%s\n",file);
	// printf("%s\n",directory);

	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("Hello message sent.\n");
	
	return 0;
}