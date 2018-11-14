#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define OK 0
#define ERROR -1

#define STD_SIZE 512

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

int main()
{
	int i;
	char *output;

	exec("find $HOME | tail", &output);

	i = 0;
	while(output[i] != '\0') {
		printf("%c", output[i]);
		i++;
	}

	free(output);

	return 0;
}