#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "../inc/tclient.h"

#define MAX 1000
#define SA struct sockaddr

typedef struct ConnectInfo{
    int PORT;
    int sockfd;
    struct sockaddr_in servaddr;
    char *finddata;
} ConnectInfo;

pthread_mutex_t mutex;

void * connectTCPClient (void *args){

    pthread_mutex_lock(&mutex);

    ConnectInfo *p = (ConnectInfo *) args;
    char *ip = malloc(MAX);
    char * buff = malloc(MAX);
    char buffer[MAX];

    askipaddress(ip);

    strcpy(buff,p->finddata);

    //if the ip address its local search in current computer
    if(strcmp(ip,"127.0.0.1") == 0) {
    	findfile(buff,ip);
    }
    else {

        //server info
	    p->servaddr.sin_family = AF_INET;
		p->servaddr.sin_addr.s_addr = inet_addr(ip);
		p->servaddr.sin_port = htons(p->PORT);
		// connect the client socket to server socket
		if (connect(p->sockfd, (SA*)(&p->servaddr), sizeof(p->servaddr)) != 0) {
			printf("connection with the server failed...\n");
			exit(0);
		}
		else
			printf("connected to the server..\n");

		printf("Presione ENTER para continuar\n");
		getchar();
		system("clear");

        //send data to server
		write(p->sockfd,buff, strlen(buff));

		bzero(buff, strlen(buff));

        //receive server data
		read(p->sockfd, buffer, sizeof(buffer));
		system("clear");
		printf("RESULTADOS DEL SERVIDOR %s \n%s",ip,buffer);
		printf("\nPor favor, presiones ENTER para continuar\n");
		getchar();

		close(p->sockfd);
	}

    pthread_mutex_unlock(&mutex);
}

void cliente_TCP(int PORT)
{
	int sockfd, count, option;
	struct sockaddr_in servaddr;
	char *findcommand = malloc(MAX);
	pthread_t *tid;
	ConnectInfo info;

	system("clear");

/**************************************OPCIONES DE INICIO******************************************/
	do {
        printf("Elegir una opcion:\n1. Comenzar una busqueda\n2. Recibir ayudar\n3. Salir\nIntroduzca el numero: ");
        scanf("%i",&option);
        system("clear");
        switch(option) {
            case 1: askfindcommand(findcommand);
            break;
            case 2: system("man find");
            break;
            case 3: return; 
        }
        system("clear");
    } while (option!=1);
/*************************************FIN OPCIONES DE INICIO***************************************/

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	count = numberservers();

	info.finddata = findcommand;
    info.PORT = PORT;
    info.sockfd = sockfd;
    info.servaddr = servaddr;

/****************************************COMIENZO DE LOS HILOS*************************************/

	tid = (pthread_t *)malloc(count * sizeof(pthread_t *));

    pthread_mutex_init(&mutex, NULL);

    //for every server to connect we create a thread
    for (int i = 0; i < count; ++i)
    {
        if (pthread_create(tid + i, NULL, &connectTCPClient, (void *)&info) != 0)
            perror("Error creating the thread");
    }

    for (int i = 0; i < count; i++) {
        if (pthread_join(tid[i], NULL) != 0) //If error ocurre
            return;
    }
    
    pthread_mutex_destroy(&mutex);

/****************************************FIN DE LOS HILOS******************************************/
}

/*******************************LLENADO DE LAS DIRECCIONES IP**************************************/
int numberservers() {
    system("clear");
    int count = 0;
    puts("Numeros de servidores a conectar");
    scanf("%i",&count);

    return count;
}
/*****************************FIN LLENADO DE LAS DIRECCIONES IP************************************/

/************************************LLENADO DEL COMANDO FIND**************************************/
void askfindcommand(char * finddata) {
    getchar();
    printf("-> SISTANXIS: find [ruta] [parámetros] [valores]\n\n");
    printf("Introduzca el comando find con su informacion:\n");
    fgets(finddata, MAX, stdin);

    if ((strlen(finddata) > 0) && (finddata[strlen (finddata) - 1] == '\n'))
        finddata[strlen (finddata) - 1] = '\0';
}
/********************************FIN LLENADO DEL COMANDO FIND**************************************/

/*************************************PEDIR LA DIRECCION IP****************************************/
void askipaddress(char * data) {

  puts("\nIntroduzca la direccion IP");
	scanf("%s",data);
	if ((strlen(data) > 0) && (data[strlen (data) - 1] == '\n'))
                data[strlen (data) - 1] = '\0';
}
/***********************************FIN PEDIR LA DIRECCION IP**************************************/

/***********************************BUSCAR EN COMPUTADOR LOCAL*************************************/
void findfile(char * buffer, char * ip) {
    system("clear");
    char * bufferito = 0;
    long length;
    
    if ((strlen(buffer) > 0) && (buffer[strlen (buffer) - 1] == '\n'))
        buffer[strlen (buffer) - 1] = '\0';
    
    printf("Comando buscado: %s\n",buffer);

    strcat(buffer," > resultado.txt");
    system(buffer);

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

    printf("\nRESULTADOS DEL SERVIDOR %s \n%s",ip,bufferito);
    remove("resultado.txt");
    printf("\nPor favor, presiones ENTER para continuar\n");
    getchar();
    getchar();
}
/*********************************FIN BUSCAR EN COMPUTADOR LOCAL***********************************/
