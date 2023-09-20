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
printf("%s\n", *env);
env++;
}
exit(0);
}
