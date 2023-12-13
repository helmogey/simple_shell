#include "shell.h"

/**
 * custom_copy_string - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @max_characters: the maximum number of characters to be copied
 * Return: the concatenated string
 */
char *custom_copy_string(char *destination, char *source, int max_characters)
{
    int index_source, index_dest;

    index_source = 0;
    while (source[index_source] != '\0' && index_source < max_characters - 1) {
        destination[index_source] = source[index_source];
        index_source++;
    }

    if (index_source < max_characters) {
        index_dest = index_source;
        while (index_dest < max_characters) {
            destination[index_dest] = '\0';
            index_dest++;
        }
    }

    return destination;
}

/*
 * Concatenate two strings, limiting the total bytes to 'max_bytes'.
 * @first: the first string
 * @second: the second string
 * @max_bytes: the maximum number of bytes to be used
 * Returns a pointer to the modified 'first' string.
 */
char *custom_concat_strings(char *first, char *second, int max_bytes)
{
    int index_first, index_second;

    index_first = strlen(first);

    index_second = 0;
    while (second[index_second] != '\0' && index_second < max_bytes) {
        first[index_first] = second[index_second];
        index_first++;
        index_second++;
    }

    if (index_second < max_bytes)
        first[index_first] = '\0';

    return first;
}


/**
 * custom_find_character - locates a character in a string
 * @string_to_search: the string to be parsed
 * @character_to_find: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *custom_find_character(char *string_to_search, char character_to_find)
{
	do {
		if (*string_to_search == character_to_find)
			return string_to_search;
	} while (*string_to_search++ != '\0');

	return NULL;
}
