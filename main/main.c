#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udp/header/cliente.h"
#include "udp/header/servidor.h"

void protocolo_UDP();
void protocolo_TCP();

int main (void){

  int opcion = 0;
  char temp[10];
  do{
    system("clear");
    printf("\n| PROYECTO DE SISTEMAS DISTRIBUIDOS |\n\n" );
    printf("Opciones: \n" );
    printf("1. Servidor UDP\n" );
    printf("2. Servidor TCP\n" );
    printf("3. Salir\n" );
    printf("Introduzca el numero: " );
    fgets(temp,10,stdin);
    strtok(temp, "\n");
    opcion = atoi(temp);
    switch(opcion){
      case 1: protocolo_UDP();
              break;
      case 2: protocolo_TCP();
              break;
    }
  }while(opcion != 3);
}

void protocolo_UDP() {
  int opcion = 0;
  system("clear");

  printf("\nEste computador servira como: \n");
  printf("1. Cliente\n" );
  printf("2. Servidor\n" );
  printf("3. Regresar\n" );
  printf("4. Salir\n");
  printf("Introduzca el numero: " );
  scanf("%i",&opcion);
  switch(opcion){
    case 1: cliente_UDP();
            break;
    case 2: servidor_UDP();
             break;
    case 3: return;
    case 4: exit(1);
  }
}

void protocolo_TCP(){
  int opcion = 0; int numero_puerto = 0; char respuesta[10]; ; char temp[10];
  do {
    system("clear");
    printf("Opciones \n");
    printf("1. servidor TCP (Procesos)\n");
    printf("2. servidor TCP (Hilos)\n");
    printf("3. Salir\n");
    printf("Introduzca el numero: " );
    fgets(temp,10,stdin);
    strtok(temp, "\n");
    opcion = atoi(temp);
    switch(opcion){
      case 1: do{
                printf("\nDeseas escribir el numero del puerto y/n (puerto por defecto 2002)\n");
                fgets(respuesta,10,stdin);
                strtok(respuesta, "\n");
                if (strcmp(respuesta,"y") == 0){
                  printf("\nEscribe el puerto: \n");
                  fgets(temp,10,stdin);
                  numero_puerto = atoi(temp);
                  // scanf("%d ",&numero_puerto);
                  // consumirNuevaLinea();
                }
                if (strcmp(respuesta,"n")==0){
                  numero_puerto = 2002;
                }
              }while ((strcmp(respuesta,"y")!=0) && (strcmp(respuesta,"n")!=0));
              printf("empieza el servidor\n");
              break;
      case 2: do{
                printf("\nDeseas escribir el numero del puerto y/n (puerto por defecto 2020)\n");
                fgets(respuesta,10,stdin);
                strtok(respuesta, "\n");
                if ((strcmp(respuesta,"y")==0)){
                  printf("\nEscribe el puerto: ");
                  fgets(temp,10,stdin);
                  numero_puerto = atoi(temp);
                }
                if ((strcmp(respuesta,"n")==0)){
                  numero_puerto = 2020;
                }
              }while ((strcmp(respuesta,"y")!=0) && (strcmp(respuesta,"n")!=0));
              break;
    }
  } while(opcion != 3);

}