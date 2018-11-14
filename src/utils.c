#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "utils.h"

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
