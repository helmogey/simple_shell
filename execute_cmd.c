
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

	command = malloc(strlen(prompt) + strlen("H_Elmogey_shell%s\n") + 3);
	printf("H_Elmogey_shell%s\n", prompt, command);

	strcpy(command, prompt);
	status = system(command);
	free(command);
	return status;
}
