#include "shell.h"
/**
*main - start
*Description: main
*Return: void
*/
char* our_shell(void) {
char *cmd = malloc(100);
fgets(cmd, 100, stdin);
return (cmd);
}