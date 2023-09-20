#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



extern char** environ;

char* our_shell(void);
void exec_shell(const char *prompt);
