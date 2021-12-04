#include <stdio.h>
#include <stdlib.h>

void main()
{
	system("gcc -g -pthread menu.c udp/client.c udp/server.c tcp/client.c tcp/fserver.c tcp/tserver.c -o mcs");
	system("./mcs");
}