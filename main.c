#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/

int main()
{
char *cmd;
int status = 1;

while (1)
{
cmd = our_shell();
cmd[strcspn(cmd, "\n")] = '\0';
if (strcmp(cmd, "exit") == 0)
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



