#include "shell.h"
/**
*error_pid - start
*Description: main
*@waitResult: input 1
*@status: input 2
*Return: void
*/
void error_pid(pid_t waitResult, int status)
{
if (waitResult == -1)
{
fprintf(stderr, "Failed to wait for child process\n");
exit(1);
}
if (WIFSIGNALED(status))
{
int signalNumber = WTERMSIG(status);
printf("Child process terminated by signal: %d\n", signalNumber);
}
}
