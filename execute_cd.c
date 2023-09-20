#include "shell.h"
/**
*execute_cd - start
*Description: main
*@command: input
*Return: void
*/
void execute_cd(const char *command)
{
int result;
const char *directory;

directory = command + 3;
result = chdir(directory);
exit(result == 0 ? 0 : 1);
}
