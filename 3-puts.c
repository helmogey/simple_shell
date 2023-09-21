#include "shell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}




void print_numbers(void)
{
int i;

for (i = 0; i <= 9; ++i)
{
_putchar(i + '0');
}
_putchar('\n');
return;
}

/**
 * puts2 - check the code
 * @str: input string
 * Return: Always 0.
 */
void puts_without_newline(char *str)
{
int l = strlen(str);
int i;

for (i = 0; i < l; i += 1)
{
_putchar(str[i]);
}
return;
}

/**
 * _puts - check the code
 * @str: input string
 * Return: Always 0.
 */
void _puts(char *str)
{
puts(str);
}
