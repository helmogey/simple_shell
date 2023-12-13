#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CUSTOM_CONVERT_LOWERCASE	1
#define CUSTOM_CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@environment: linked list local copy of environ
 *@environ: custom modified copy of environ from LL environment
 *@history: the history node
 *@aliases: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *filename;
	list_t *environment;
	list_t *history;
	list_t *aliases;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int loophsh(char **);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int if_excute(info_t *, char *);
char *c_duplicated(char *, int, int);
char *which_pth(info_t *, char *, char *);
int l_string(char *);
int strs_comp(char *, char *);
char *hystck(const char *, const char *);
char *concat_Str(char *, char *);
void my_puts(char *str);
int my_putchar(char c);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);
char *custom_copy_string(char *destination, char *source, int max_characters);
char *custom_concat_strings(char *first, char *second, int max_bytes);
char *custom_find_character(char *string_to_search, char character_to_find);
char *copy_str(char *, char *);
char *duplicating_str(const char *);
void my_put_str(char *);
int _putchar(char);
char **wrd_str(char *, char *);
char **str_Split_wrd(char *, char);
int addr_null(void **);
char *cst_memory(char *, char, unsigned int);
void str_free(char **);
void *memory_allocat(void *, unsigned int, unsigned int);
int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char *delimiters);
int is_alpha_character(int c);
int convert_string_to_integer(char *s);
int ch_dir(info_t *info);
int my_exit(info_t *info);
int my_help(info_t *info);
int _erratoi(char *str);
void print_error(info_t *, char *);
int print_custom_decimal(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void remove_custom_comments(char *buffer);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
int display_history(info_t *info);
int manage_alias(info_t *info);
char *get_environment_variable(info_t *info, const char *name);
int display_environment(info_t *info);
int set_environment_variable(info_t *info);
int unset_environment_variable(info_t *info);
int populate_environment_list(info_t *info);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
list_t *custom_add_node_at_start(list_t **, const char *, int);
list_t *custom_add_node_at_end(list_t **, const char *, int);
size_t custom_print_str_list(const list_t *);
int custom_delete_node_at_index(list_t **, unsigned int);
void custom_free_l(list_t **);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
size_t custom_l_length(const list_t *);
char **custom_list_into_strings(list_t *);
size_t printing_l(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t get_node_idx(list_t *, list_t *);
int buf_char(info_t *, char *, size_t *);
void if_cnt_chain(info_t *, char *, size_t *, size_t, size_t);
int str_in_alias(info_t *);
int replace_vars_in_str(info_t *);
int rplc_str(char **, char *);
#endif
