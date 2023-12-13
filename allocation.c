#include "shell.h"

/**
 **cst_memory - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *cst_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * str_free - frees a string of strings
 * @pp: string of strings
 */
void str_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * memory_allocat - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *memory_allocat(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr) {
        return malloc(new_size);
    }
    if (!new_size) {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size) {
        return ptr;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL;
    }
    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--) {
        new_ptr[old_size] = ((char *)ptr)[old_size];
    }
    free(ptr);
    return new_ptr;
}