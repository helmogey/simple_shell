
#include "shell.h"
/**
*exec_shell - start
*Description: main
*Return: void
*/

/*
int exec_shell(const char *prompt)
{
	int status;
	char *command;

	command = malloc(strlen(prompt) + 1);
	if (command == NULL)
	{
	return (-1);
	}
	strcpy(command, prompt);
	status = system(command);
	free(command);
	return (status);
}
*/
/*
void exec_shell(const char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        int result = system(command);
        exit(result);
    } else {
        int status;
        pid_t waitResult = waitpid(pid, &status, 0);

        if (waitResult == -1) {
            fprintf(stderr, "Failed to wait for child process\n");
            exit(1);
        }

        if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
			if (exitStatus != 0)
			{
            printf("Child process exited with status: %d\n", exitStatus);
			}
        } else if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
            printf("Child process terminated by signal: %d\n", signalNumber);
        }
    }
}

*/


/*
void exec_shell(const char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ') {
            const char* directory = command + 3;
            int result = chdir(directory);
            exit(result == 0 ? 0 : 1);
        } else {
            int result = system(command);
            exit(result);
        }
    } else {
        int status;
        pid_t waitResult = waitpid(pid, &status, 0);

        if (waitResult == -1) {
            fprintf(stderr, "Failed to wait for child process\n");
            exit(1);
        }

          if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
            printf("Child process terminated by signal: %d\n", signalNumber);
        }
    }
}

*/



extern char** environ;

void exec_shell(const char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ') {
            const char* directory = command + 3;
            int result = chdir(directory);
            exit(result == 0 ? 0 : 1);
        } else if (command[0] == 'e' && command[1] == 'n' && command[2] == 'v' && command[3] == '\0') {
            char** env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
            exit(0);
        } else {
            int result = system(command);
            exit(result);
        }
    } else {
        int status;
        pid_t waitResult = waitpid(pid, &status, 0);

        if (waitResult == -1) {
            fprintf(stderr, "Failed to wait for child process\n");
            exit(1);
        }

        if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
            printf("Child process terminated by signal: %d\n", signalNumber);
        }
    }
}




