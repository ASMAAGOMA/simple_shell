#include "shell.h"

/**
 * _putchar - putchar function
 * @c: the string
 * Return: 1
 */

int _putchar(char c)
{
	static int t;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || t >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, t);
		t = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[t++] = c;
	return (1);
}

/**
 * _puts - puts function
 * @string: the string
 */

void _puts(char *string)
{
	int t = 0;

	if (!string)
		return;
	while (string[t] != '\0')
	{
		_putchar(string[t]);
		t++;
	}
}
