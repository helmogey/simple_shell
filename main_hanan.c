#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/
int main()
{
	int status;

	status = exec_shell("ls");
	if (status != 0) {
		printf("Error executing shell: %d\n", status);
		return 1;
	}
	return 0;
}
