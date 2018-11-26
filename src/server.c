#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define OK 0
#define ERROR -1
#define STD_SIZE 512

#define PORT 8080

int create_socket(int port, int *socket_desc, struct sockaddr_in *server,
		  int isTCP);
int update_client();
int listen_client();
int menu();

int create_socket(int port, int *socket_desc, struct sockaddr_in *server,
		  int isTCP)
{
	if (isTCP) // 1
		(*socket_desc) = socket(AF_INET, SOCK_STREAM, 0);
	else // 0
		(*socket_desc) = socket(AF_INET, SOCK_DGRAM, 0);

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

int listen_client()
{
	int socket_desc, client_size, recv_size;
	struct sockaddr_in server, client;
	char buffer[STD_SIZE];

	client_size = sizeof(client);

	if (create_socket(PORT + 1, &socket_desc, &server, 0) == ERROR)
		return ERROR;

	while (1) {
		recv_size = recvfrom(socket_desc, buffer, sizeof(buffer), 0,
				     (struct sockaddr *)&client, &client_size);
		printf("[%s:%d] [%s]\n", inet_ntoa(client.sin_addr),
		       ntohs(client.sin_port), buffer);
	}

	return OK;
}

int update_client()
{
	int socket_desc;
	struct sockaddr_in server;

	int new_socket, c;
	struct sockaddr_in client;
	char buffer[STD_SIZE];
	size_t flag = 0;
	FILE *file_to_send;

	if (create_socket(PORT, &socket_desc, &server, 1) == ERROR)
		return ERROR;

	printf("Waiting for connections...\n");
	listen(socket_desc, 1);

	new_socket = accept(socket_desc, (struct sockaddr *)&client,
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

int menu()
{
	short user_command;

	printf("[0] Update client\n");
	printf("[1] Listen for ping\n");
	printf("> ");

	scanf("%hd", &user_command);

	switch (user_command) {
	case 0:
		system("clear");
		update_client();
		break;
	case 1:
		system("clear");
		listen_client();
		break;

	default:
		printf("Option not found\n");
	}
}

int main()
{
	menu();
}