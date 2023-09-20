#include "shell.h"
/**
*exec_shell - start
*Description: main
*@command: input
*Return: void
*/
void exec_shell(const char *command)
{
pid_t pid = fork();
int status;

if (pid < 0)
{
fprintf(stderr, "Fork failed\n");
exit(1);
}
else if (pid == 0)
{
if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
{
execute_cd(command);
}
else if (strcmp(command, "env") == 0)
{
execute_env();
}
else
{
int result = system(command);
exit(result);
}
}
else
{
pid_t waitResult = waitpid(pid, &status, 0);
error_pid(waitResult, status);
}
}
