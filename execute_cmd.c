#include "shell.h"
/**
*exec_shell - start
*Description: main
*command: input
*Return: void
*/
void exec_shell(const char* command)
{
pid_t pid = fork();
int result, status;

if (pid < 0)
{
fprintf(stderr, "Fork failed\n");
exit(1);
}
else if (pid == 0)
{
if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
{
const char* directory = command + 3;
result = chdir(directory);
exit(result == 0 ? 0 : 1);
}
else if (command[0] == 'e' && command[1] == 'n' && command[2] == 'v' && command[3] == '\0')
{
char** env = environ;
while (*env != NULL)
{
printf("%s\n", *env);
env++;
}
exit(0);
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
}