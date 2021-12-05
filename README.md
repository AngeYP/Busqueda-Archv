# Busqueda-Archv

Este proyecto cumple con la finalidad de hacer una búsqueda entre clientes y servidores mediante los protocolos UDP y TCP. Dicha búsqueda se aplicará al estilo comando find de linux.
El proyecto está divido en 3 partes:
  -> Menu de inicio y el main:
    - Main: será el único .c que se ejecute en la terminal, este contiene las instrucciones para ejecutar todos .c.
    - Menu: estarán las opciones para elegir el protocolo que desee.
  -> En la carpeta UDP:
    - Código del cliente, el cual crea un hilo para cada uno de los servidores en los que se desea hacer la búsqueda, o también buscar en el computador local.
    - Código del servidor.
    - Headers para las funciones.
  -> En la carpeta TCP:
    Código del cliente, el cual crea un hilo para cada uno de los servidores en los que se desea hacer la búsqueda, o también buscar en el computador local.
    Código del servidor mediante hilos.
    Código del servidor mediante procesos.
    Headers para las funciones.
