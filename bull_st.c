#include "shell.h"

/**
 * my_help - displays help information
 * @info: pointer to the info struct
 *
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	if (0)
		my_puts(*arg_array);

	return (0);
}

/**
 * my_exit - exits the shell
 * @info: pointer to the info struct
 *
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			my_puts(info->argv[1]);
			my_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: pointer to the info struct
 *
 * Return: Always 0
 */

int ch_dir(info_t *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        my_puts("couldn.t change\n");

    if (!info->argv[1])
	{
        target_dir = get_environment_variable(info, "HOME=");
        if (!target_dir)
            chdir_ret = chdir((target_dir = get_environment_variable(info, "PWD=")) ? target_dir : "/");
        else
            chdir_ret = chdir(target_dir);
    }
	else if (strs_comp(info->argv[1], "-") == 0)
	{
        if (!get_environment_variable(info, "OLDPWD="))
		{
            my_puts(current_dir);
            _putchar('\n');
            return (1);
        }
        my_puts(get_environment_variable(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((target_dir = get_environment_variable(info, "OLDPWD=")) ? target_dir : "/");
    }
	else
	{
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        my_puts(info->argv[1]);
        my_putchar('\n');
    } else {
        _setenv(info, "OLDPWD", get_environment_variable(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}


/**
 * display_history - Displays the history list, one command per line,
 *                   preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    printing_l(info->history);
    return (0);
}

/**
 * remove_alias - Removes an alias identified by a string.
 * @info: Parameter struct.
 * @alias_str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias_str)
{
    char *equal_sign, c;
    int ret;

    equal_sign = custom_find_character(alias_str, '=');
    if (!equal_sign)
        return (1);

    c = *equal_sign;
    *equal_sign = 0;
    
    ret = custom_delete_node_at_index(&(info->aliases),
        get_node_idx(info->aliases, node_start(info->aliases, alias_str, -1)));

    *equal_sign = c;
    return (ret);
}

/**
 * add_alias - Adds an alias identified by a string.
 * @info: Parameter struct.
 * @alias_str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(info_t *info, char *alias_str)
{
    char *equal_sign;

    equal_sign = custom_find_character(alias_str, '=');
    if (!equal_sign)
        return (1);

    if (!*++equal_sign)
        return remove_alias(info, alias_str);

    remove_alias(info, alias_str);
    return (custom_add_node_at_end(&(info->aliases), alias_str, 0) == NULL);
}

/**
 * print_single_alias - Prints the information about a single alias.
 * @alias_node: The alias node.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_single_alias(list_t *alias_node)
{
    char *equal_sign_position = NULL, *alias_name = NULL;

    if (alias_node)
    {
        equal_sign_position = custom_find_character(alias_node->str, '=');
        for (alias_name = alias_node->str; alias_name <= equal_sign_position; alias_name++)
            _putchar(*alias_name);
        
        _putchar('\'');
        my_put_str(equal_sign_position + 1);
        my_put_str("'\n");

        return (0);
    }

    return (1);
}

/**
 * manage_alias - Manages alias commands, mimicking the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info)
{
    int i = 0;
    char *equal_sign_position = NULL;
    list_t *alias_node = NULL;

    if (info->argc == 1)
    {
        alias_node = info->aliases;
        while (alias_node)
        {
            print_single_alias(alias_node);
            alias_node = alias_node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        equal_sign_position = custom_find_character(info->argv[i], '=');

        if (equal_sign_position)
            add_alias(info, info->argv[i]);
        else
            print_single_alias(node_start(info->aliases, info->argv[i], '='));
    }

    return (0);
}
