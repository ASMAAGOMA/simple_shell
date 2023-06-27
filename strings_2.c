#include "shell.h"

/**
 * string_copy - function to copy a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to the destination
 */

char *string_copy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * string_duplication - function to duplicate the string
 * @string: the string to be duplicated
 * Return: the value of end
 */
char *string_duplication(const char *string)
{
	int len = 0;
	char *end;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	end = malloc(sizeof(char) * (len + 1));

	if (!end)
		return (NULL);
	for (len++; len--;)
		end[len] = *--string;
	return (end);
}
