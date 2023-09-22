#ifndef OUR_SHELL
#define OUR_SHELL
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



extern char **environ;

char *our_shell(void);
void exec_shell(char *prompt);
void execute_env(void);
void execute_cd(char *command);
void error_pid(pid_t waitResult, int status);
int _strcmp(char *s1, char *s2);
void _puts(char *str);
int _putchar(char c);
void puts_without_newline(char *str);
int _strlen(char *s);
#endif
