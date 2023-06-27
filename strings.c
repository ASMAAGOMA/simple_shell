#include "shell.h"

/**
 * string_length - function to calculate the lengtl of the string
 * @string: the string to calculate the length of it
 * Return: the value of end whan success
 */

int string_length(char *string)
{
	int t = 0;

	if (!string)
		return (0);
	while (*string++)
		t++;
	return (t);
}

/**
 * string_cmp - compares betwwen two strings
 * @string1: the first string
 * @string2: the second string
 * Return: 0(failure)
 */

int string_cmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (string1 == string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starting - checking if need is starting with hay
 * @hay: the searchad string
 * @need: the string to find
 * Return: next char hay or null
 */

char *starting(const char *hay, const char *need)
{
	while (*need)
	{
		if (*need++ != *hay++)
			return (NULL);
	}
	return ((char *)hay);
}

/**
 * string_cat - concencates two strings
 * @dest: destination
 * @src: source
 * Return: pointer to destination
 */

char *string_cat(char *dest, char *src)
{
	char *end = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (end);
}
