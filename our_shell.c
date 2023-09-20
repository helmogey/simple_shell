#include "shell.h"
/**
*our_shell - start
*Description: main
*Return: void
*/
char *our_shell(void)
{
char *cmd = malloc(100);

printf("ourshell$");
fgets(cmd, 100, stdin);
return (cmd);
}
