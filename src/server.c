#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define OK 0
#define ERROR -1
#define STD_SIZE 512

int create_socket(int port, int *socket_desc, struct sockaddr_in *server);
int update_client(int *socket_desc, struct sockaddr_in *server);
int menu(int *socket_desc, struct sockaddr_in *server);

int create_socket(int port, int *socket_desc, struct sockaddr_in *server)
{
	(*socket_desc) = socket(AF_INET, SOCK_STREAM, 0);
	if ((*socket_desc) == -1) {
		printf("Could not create socket");
	}

	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons(port);

	if (bind((*socket_desc), (struct sockaddr *)&(*server),
		 sizeof(*server)) < 0) {
		printf("Bind failed\n");
		return ERROR;
	}

	return OK;
}

int update_client(int *socket_desc, struct sockaddr_in *server)
{
	int new_socket, c;
	struct sockaddr_in client;
	char buffer[STD_SIZE];
	size_t flag = 0;
	FILE *file_to_send;

	printf("Waiting for connections...\n");
	listen(*socket_desc, 1);

	new_socket = accept(*socket_desc, (struct sockaddr *)&client,
			    (socklen_t *)&c);

	file_to_send = fopen("../ezekiel", "r");
	if (!file_to_send) {
		printf("Error opening file\n");
		return -1;
	}

	do {
		flag = fread(buffer, sizeof(buffer), 1, file_to_send);
		write(new_socket, buffer, sizeof(buffer));
	} while (flag > 0);

	fclose(file_to_send);
	close(new_socket);

	return 0;
}

int menu(int *socket_desc, struct sockaddr_in *server)
{
	short user_command;

	printf("[0] Update client\n");
	printf("[1] Nothing\n");
	printf("> ");

	scanf("%hd", &user_command);

	switch (user_command) {
	case 0:
		system("clear");
		update_client(socket_desc, server);
		break;
	default:
		printf("Option not found\n");
	}
}

int main()
{
	int socket_desc;
	struct sockaddr_in server;

	if (create_socket(8080, &socket_desc, &server) == ERROR)
		return ERROR;

	menu(&socket_desc, &server);
}