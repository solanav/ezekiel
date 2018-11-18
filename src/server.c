#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char buffer[512];
	size_t flag = 0;
	FILE *file_to_send;

	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);

	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("Bind failed\n");
		return 1;
	}

	listen(socket_desc, 1);

	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);

	file_to_send = fopen("ezekiel", "r");
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