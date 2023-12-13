#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = get_environment_variable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (l_string(dir) + l_string(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_str(buf, dir);
	concat_Str(buf, "/");
	concat_Str(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		my_putsfd(node->str, fd);
		my_putfd('\n', fd);
	}
	my_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    struct stat st;
    if (fstat(fd, &st) || st.st_size < 2) {
        close(fd);
        return 0;
    }

    char *buf = malloc(sizeof(char) * (st.st_size + 1));
    if (!buf) {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';

    if (rdlen <= 0) {
        free(buf);
        close(fd);
        return 0;
    }

    close(fd);

    int last = 0, linecount = 0;
    for (int i = 0; i < st.st_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    // Process the last line if not processed
    if (last != st.st_size)
        build_history_list(info, buf + last, linecount++);

    // Free the buffer
    free(buf);

    // Update history count
    info->histcount = linecount;

    // Delete excess history nodes
    while (info->histcount-- >= HIST_MAX)
        custom_delete_node_at_index(&(info->history), 0);

    // Renumber the history list
    renumber_history(info);

    // Return the final history count
    return info->histcount;
}


/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	custom_add_node_at_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
