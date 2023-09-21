#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/
int main(void)
{
char *cmd;
int status = 1;
size_t len;

while (1)
{
cmd = our_shell();
len = _strlen(cmd);
if (len > 0 && cmd[len - 1] == '\n')
{
cmd[len - 1] = '\0';
}if (_strcmp(cmd, "exit") == 0)
{
status = 98;
break;
}
else
{
exec_shell(cmd);
}
}
return (status);
}



