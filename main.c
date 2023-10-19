#include "shell.h"
/**
*main - start
*Description: main
*@argv: input
*@argc: input
*Return: void
*/
int main(int argc, char **argv)
{
char *cmd = NULL;
int status = 1;
size_t len;

if (argc > 1)
{
cmd = argv[1];
exec_shell(cmd);
}
else
{
while (1)
{
cmd = our_shell();
status = 0;
if (!cmd || !*cmd)
{
break;
}
len = _strlen(cmd);
if (len > 0 && cmd[len - 1] == '\n')
{
cmd[len - 1] = '\0';
}
if (_strcmp(cmd, "exit") == 0)
{
status = 2;
break;
}
else
{
exec_shell(cmd);
}
}
}
free(cmd);
return (status);
}



