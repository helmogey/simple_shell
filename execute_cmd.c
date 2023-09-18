
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

	command = malloc(strlen(prompt) + 1);
	if (command == NULL)
	{
	return (-1);
	}
	strcpy(command, prompt);
	status = system(command);
	free(command);
	return (status);
}
