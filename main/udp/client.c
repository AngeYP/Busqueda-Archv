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
#include <pthread.h>
#include "header/cliente.h"
  
//#define PORT 2002
#define MAXLINE 1000
#define MAXFIND 500

typedef struct ConnectInfo{
    int PORT;

    char *finddata;
} ConnectInfo;

pthread_mutex_t mutex;

void * connectClient (void *args){

    pthread_mutex_lock(&mutex);

    char buffer[100];
    int sockfd, n;
    struct sockaddr_in servaddr;
    ConnectInfo *p = (ConnectInfo *) args;
    char *ip = malloc(MAXFIND);

    askipadress(ip);

    bzero(&servaddr, sizeof(ip));
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(p->PORT);
    servaddr.sin_family = AF_INET;
      
    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      
    // connect to server

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }
  
    sendto(sockfd, p->finddata, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
      
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    system("clear");
    printf("RESULTADOS DEL SERVIDOR %s \n%s",ip,buffer);
    printf("\nPor favor, presiones ENTER para continuar\n");
    getchar();

    close(sockfd);

    pthread_mutex_unlock(&mutex);
}
  
// Driver code
void cliente_UDP(int PUERTO) {

    system("clear");

    int count = 0;
    char filename[] = "DireccionesIP.txt";
    char *findcommand = malloc(MAXFIND);
    ConnectInfo info;
    int option = 0;
    pthread_t *th;
    char *ip = malloc(15);
    char aux [1000];

/**************************************OPCIONES DE INICIO******************************************/
    do {
        printf("Elegir una opcion:\n1. Comenzar una busqueda\n2. Recibir ayudar\n3. Salir\nIntroduzca el numero: ");
        scanf("%i",&option);
        system("clear");
        switch(option) {
            case 1: askfind(findcommand);
            break;
            case 2: system("man find");
            break;
            case 3: return; 
        }
        system("clear");
    } while (option!=1);

    count = numberserv();

    //count = askipadress(filename);
/*************************************FIN OPCIONES DE INICIO***************************************/
    
    info.finddata = findcommand;
    info.PORT = PUERTO;

/*************************************BUSCA EN EL ARCHIVO******************************************/
/********************************************FIN***************************************************/

/****************************************COMIENZO DE LOS HILOS*************************************/
    th = (pthread_t *)malloc(count * sizeof(pthread_t *));

    pthread_mutex_init(&mutex, NULL);

    FILE *file = fopen (filename, "r" );
    for (int i = 0; i < count; ++i)
    {
        if (pthread_create(th + i, NULL, &connectClient, (void *)&info) != 0)
            perror("Error creating the thread");
    }

    //ERROR INFINITY LOOP 

    for (int i = 0; i < count; i++) {
        if (pthread_join(th[i], NULL) != 0) //If error ocurre
            return;
    }
    
    pthread_mutex_destroy(&mutex);
/******************************************FIN DE LOS HILOS****************************************/
}


/**********************************LLENADO DEL COMANDO FIND****************************************/
void askfind(char * finddata) {
    getchar();
    printf("Introduzca el comando find con su informacion\n");
    fgets(finddata, MAXFIND, stdin);

    if ((strlen(finddata) > 0) && (finddata[strlen (finddata) - 1] == '\n'))
        finddata[strlen (finddata) - 1] = '\0';
}
/********************************FIN LLENADO DEL COMANDO FIND**************************************/

/*******************************LLENADO DE LAS DIRECCIONES IP**************************************/
int numberserv() {
    system("clear");
    int count = 0;
    puts("Numeros de servidores a conectar");
    scanf("%i",&count);

    return count;
}
/*****************************FIN LLENADO DE LAS DIRECCIONES IP************************************/

void askipadress(char * ip) {
    getchar();
    printf("Introduzca la direccion IP\n");
    fgets(ip, MAXFIND, stdin);

    if ((strlen(ip) > 0) && (ip[strlen (ip) - 1] == '\n'))
        ip[strlen (ip) - 1] = '\0';
}