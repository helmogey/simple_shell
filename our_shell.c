#include "shell.h"
/**
*our_shell - start
*Description: main
*Return: void
*/
char *our_shell(void)
{
char *cmd = NULL;
size_t len = 0;
ssize_t nread;
/*puts_without_newline("ourshell$");*/
nread = getline(&cmd, &len, stdin);
if (nread == -1)
{
free(cmd);
return (NULL);
}

if (len > 0 && cmd[len - 1] == '\n')
{
cmd[len - 1] = '\0';
}
return (cmd);
}
