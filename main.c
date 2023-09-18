#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/

int main()
{
char *cmd;
int status;

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
status =  exec_shell(cmd);
if (status == -1)
{
printf("Error alocating memory");
return (-1);
}
printf("%d\n", status);
}
}
return (1);
}





