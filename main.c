#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/

int main()
{
char *cmd;

while (1)
{
cmd = our_shell();
cmd[strcspn(cmd, "\n")] = '\0';
if (strcmp(cmd, "exit") == 0)
{
break;
}
else
{
exec_shell(cmd);
}
}
return (1);
}





