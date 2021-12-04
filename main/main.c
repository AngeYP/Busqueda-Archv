#include <stdio.h>
#include <stdlib.h>

void main()
{
	system("gcc menu.c udp/client.c udp/server.c tcp/client.c tcp/fserver.c -o mcs");
	system("./mcs");
}