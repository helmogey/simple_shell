#include "shell.h"
/**
*exec_shell - start
*Description: main
*@command: input
*Return: void
*/
void exec_shell(char *command)
{
pid_t pid = fork();
int result, status, pipefd[2];

if (pipe(pipefd) == -1)
{
fprintf(stderr, "Pipe creation failed\n");
exit(1);
}

if (pid < 0)
{
_puts("Fork failed");
exit(1);
}
else if (pid == 0)
{
close(pipefd[0]);
dup2(pipefd[1], STDIN_FILENO);
if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
{
execute_cd(command);
}
else if (_strcmp(command, "env") == 0)
{
execute_env();
}
else
{
close(pipefd[1]);
write(pipefd[0], command, strlen(command) + 1);
result = system(command);
exit(result);
}
}
else
{
pid_t waitResult = waitpid(pid, &status, 0);
error_pid(waitResult, status);
}
}
