#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udp/header/cliente.h"
#include "udp/header/servidor.h"
#include "tcp/header/client.h"
#include "tcp/header/fserver.h"

void protocolo_UDP();
void protocolo_TCP();

int main (void){

  int opcion = 0;
  char temp[10];
  do{
    system("clear");
    puts("\n| PROYECTO DE SISTEMAS DISTRIBUIDOS |\n\nOpciones: \n1. Protocolo UDP\n2. Protocolo TCP\n3. Salir");
    printf("Introduzca el numero para el protocolo: " );
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
  char * portopt = malloc(1);
  int port = 2002;
  system("clear");
  puts("Desea cambiar el puerto y/n (Puerto predeterminado: 2002)\n");
  scanf("%s",portopt);
  if (portopt[0] == 'y') {
    printf("\nIntroduzca el numero del puerto: ");
    scanf("%i",&port);
  }
  system("clear");
  puts("Este computador servira como: \n1. Cliente\n2. Servidor\n3. Regresar\n4. Salir");
  printf("Introduzca el numero a usar en el computador: " );
  scanf("%i",&opcion);
  switch(opcion){
    case 1: cliente_UDP(port);
            break;
    case 2: servidor_UDP(port);
             break;
    case 3: return;
    case 4: exit(1);
  }
}

void protocolo_TCP(){
  int opcion = 0; int numero_puerto = 0; char respuesta[10]; ; char temp[10];
  int opcport = 0;
  system("clear");
  puts("Este computador servira como: \n1. Cliente\n2. Servidor\n3. Regresar\n4. Salir\n");
  printf("Introduzca el numerito a usar en el computador: ");
  scanf("%i",&opcion);
  switch(opcion){
    case 1: {
      system("clear");
      puts("Escriba el numero del puerto:\n1. Servidor con procesos (2002)\n2. Servidor con hilos (2020)\n3. Nuevo puerto\n4. Salir\n");
      printf("Introduzca una opcion: ");
      scanf("%i",&opcport);
      switch(opcport){
        case 1: cliente_TCP(2002); break;
        case 2: cliente_TCP(2020); break;
        case 3: {
          printf("\nIntroduzca el numero del puerto: " );
          scanf("%i",&numero_puerto);
          system("clear");
          cliente_TCP(numero_puerto);
        } break;
      }
        default: return;
    }
    //SERVIDORES
    case 2: {
      do {
        system("clear");
        puts("Opciones\n1. servidor TCP (Procesos)\n2. servidor TCP (Hilos)\n3. Salir\n");
        puts("Introduzca una opcion");
        fgets(temp,10,stdin);
        strtok(temp, "\n");
        opcion = atoi(temp);
        switch(opcion){
          case 1: do{
            puts("\nDeseas escribir el numero del puerto y/n (puerto por defecto 2002)\n");
            fgets(respuesta,10,stdin);
            strtok(respuesta, "\n");
            if (strcmp(respuesta,"y") == 0){
              printf("\nEscribe el puerto: \n");
              fgets(temp,10,stdin);
              numero_puerto = atoi(temp);
            } else if (strcmp(respuesta,"n")==0){
              numero_puerto = 2002;
            }
          }while ((strcmp(respuesta,"y")!=0) && (strcmp(respuesta,"n")!=0));
          fserver_TCP(numero_puerto);
          break;

          case 2: do{
            puts("\nDeseas escribir el numero del puerto y/n (puerto por defecto 2020)\n");
            fgets(respuesta,10,stdin);
            strtok(respuesta, "\n");
            if ((strcmp(respuesta,"y")==0)){
              printf("\nEscribe el puerto: ");
              fgets(temp,10,stdin);
              numero_puerto = atoi(temp);
            } else if ((strcmp(respuesta,"n")==0)){
              numero_puerto = 2020;
            }
          }while ((strcmp(respuesta,"y")!=0) && (strcmp(respuesta,"n")!=0));
          //tserver_TCP(numero_puerto);
          break;
        }
      } while(opcion != 3);
    }
    case 3: return;
    case 4: exit(1);
  }
}