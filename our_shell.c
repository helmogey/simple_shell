#include "shell.h"
/**
*our_shell - start
*Description: main
*Return: void
*/

/*
char *our_shell(void)
{
char *cmd = malloc(100);
size_t len = strlen(cmd);

puts_without_newline("ourshell$");
fgets(cmd, 100, stdin);
if (len > 0 && cmd[len - 1] == '\n')
{
cmd[len - 1] = '\0';
}
return (cmd);
}
*/





char *our_shell(void)
{
char *cmd = NULL;
size_t len = 0;
ssize_t nread;



nread = getline(&cmd, &len, stdin);

if (nread == -1)
{
free(cmd);
_puts("\n");
return (NULL);
}
/*puts_without_newline("ourshell$");*/
if (len > 0 && cmd[len - 1] == '\n')
{
cmd[len - 1] = '\0';
}
return (cmd);
}