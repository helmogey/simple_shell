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

cmd = our_shell();
status =  exec_shell(cmd);
printf("%d", status);
return (1);
}





