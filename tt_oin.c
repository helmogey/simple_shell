#include "shell.h"

/**
 * is_shell_interactive - checks if the shell is in interactive mode
 * @info: pointer to the info struct
 *
 * Return: 1 if shell is in interactive mode, 0 otherwise
 */
int is_shell_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_character_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_character_delimiter(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters == c)
			return (1);
		delimiters++;
	}
	return (0);
}

/**
 * is_alpha_character - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alpha_character(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string_to_integer - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the converted integer value, or 0 if no numbers in the string
 */
int convert_string_to_integer(char *s)
{
	int sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (int i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
