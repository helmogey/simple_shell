#include "shell.h"
/**
*execute_env - start
*Description: main
*Return: void
*/
void execute_env(void)
{
char **env = environ;

while (*env != NULL)
{
_puts(*env);
env++;
}
exit(0);
}
