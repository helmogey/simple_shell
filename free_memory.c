#include "shell.h"
/**
*free_memory - start
*Description: main
*@ptr: input
*Return: void
*/
void free_memory(char **ptr)
{
int i;

for (i = 0; ptr[i]; i++)
{
free((ptr[i]));
}
free(ptr);
}

