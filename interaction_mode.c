#include "shell.h"

/**
 * is_interact - true if interactive mode
 * @information: struct
 * Return: 0 or 1
 */
int is_interact(information_t *information)
{
	return (isatty(STDIN_FILENO) && information->read_file_discriptor);
}

/**
 * is_delimeter - is the char delimeter or not
 * @s: char
 * @delimeter: the delimeter
 * Return: 0 or 1
 */

int is_delimeter(char s, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == s)
			return (1);
	return (0);
}

/**
 * alphabetic - checks if char is alphabet or not
 * @s: char
 * Return: 0 or 1
 */
int alphabetic(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * my_atoi - string to integer
 * @string: string to convert
 * Return: 0 or 1
 */

int my_atoi(char *string)
{
	int t, s = 1, f = 0, out;
	unsigned int final = 0;

	for (t = 0; string[t] != '\0' && f != 2; t++)
	{
		if (string[t] == '-')
			s *= -1;
		if (string[t] >= '0' && string[t] <= '9')
		{
			f = 1;
			final *= 10;
			final += (string[t] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (s == -1)
		out = -final;
	else
		out = final;
	return (out);
}

