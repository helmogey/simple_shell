#include "shell.h"

/**
 * display_environment - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_environment(info_t *info)
{
    custom_print_str_list(info->environment);
    return (0);
}
/**
 * get_environment_variable - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->environment;
    char *p;

    while (node)
    {
        p = hystck(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }

    return (NULL);
}
/**
 * set_environment_variable - Initializes a new environment variable
 *                            or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        my_puts("Incorrect number of arguments\n");
        return (1);
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);

    return (1);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        my_puts("Too few arguments.\n");
        return (1);
    }

    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        custom_add_node_at_end(&node, environ[i], 0);

    info->environment = node;
    return (0);
}




/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = custom_list_into_strings(info->environment);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->environment;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = hystck(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = custom_delete_node_at_index(&(info->environment), i);
			i = 0;
			node = info->environment;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(l_string(var) + l_string(value) + 2);
	if (!buf)
		return (1);
	copy_str(buf, var);
	concat_Str(buf, "=");
	concat_Str(buf, value);
	node = info->environment;
	while (node)
	{
		p = hystck(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	custom_add_node_at_end(&(info->environment), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
