
#include "shell.h"
/**
*exec_shell - start
*Description: main
*Return: void
*/

int exec_shell(const char *prompt)
{
	int status;
	char *command;

	command = malloc(strlen(prompt) + strlen("%s elmogey%s\n") + 3);
	printf("%s elmogey %s\n", command, prompt);

	strcpy(command, prompt);
	status = system(command);
	free(command);
	return status;
}
