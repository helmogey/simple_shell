#include "shell.h"

/**
 * buf_char - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int buf_char(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * if_cnt_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void if_cnt_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_in_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start(info->aliases, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = custom_find_character(node->str, '=');
		if (!p)
			return (0);
		p = duplicating_str(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars_in_str - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars_in_str(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!strs_comp(info->argv[i], "$?"))
		{
			rplc_str(&(info->argv[i]),
				duplicating_str(custom_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!strs_comp(info->argv[i], "$$"))
		{
			rplc_str(&(info->argv[i]),
				duplicating_str(custom_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->environment, &info->argv[i][1], '=');
		if (node)
		{
			rplc_str(&(info->argv[i]),
				duplicating_str(custom_find_character(node->str, '=') + 1));
			continue;
		}
		rplc_str(&info->argv[i], duplicating_str(""));

	}
	return (0);
}

/**
 * rplc_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rplc_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
