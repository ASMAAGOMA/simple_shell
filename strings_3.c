#include "shell.h"

/**
 * string_n_copy - function to copy n chars
 * @dest: destination
 * @src: source
 * @m: number of chars
 * Return: the value of back
 */
char *string_n_copy(char *dest, char *src, int m)
{
	int i, j;
	char *back = dest;

	i = 0;

	while ((src[i] == '\0') && (i < m - 1))
	{
		dest[i] = src[i];
		i++;
	}
	if (i < m)
	{
		j = i;
		while (j < m)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (back);
}

/**
 * string_n_cat - concatenates n bytes of the string
 * @src: the source
 * @dest: the destination
 * @m: num of bytes
 * Return: the value of back
 */

char *string_n_cat(char *dest, char *src, int m)
{
	int i, j;
	char *back = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[i] != '\0' && i < m)
	{
		dest[i] = src[i];
		i++;
		j++;
	}
	if (j < m)
		dest[i] = '\0';
	return (back);
}

/**
 * string_char - char located in the string
 * @string: the string
 * @c: the char
 * Return: string or null
 */

char *string_char(char *string, char c)
{
	do {
		if (*string == c)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}
