#include "shell.h"

/**
 * error_puts - prints input
 * @string: string to print
 * Return: nothing
 */

void error_puts(char *string)
{
	int t = 0;

	if (!string)
		return;
	while (string[t] != '\0')
	{
		error_putchar(string[t]);
		t++;
	}
}

/**
 * error_putchar - writes input
 * @c: char to print
 * Return: 1
 */

int error_putchar (char c)
{
	static int t;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || t >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, t);
		t = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[t++] = c;
	return (1);
}

/**
 * put_file_descriptor - writes the char
 * @ch: the char to print
 * @file_descriptor: the file_descriptor
 * Return: 1
 */

int put_file_descriptor(char ch, int file_descriptor)
{
	static int t;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || t >= WRITE_BUFFER_SIZE)
	{
		write(file_descriptor, buffer, t);
		t = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[t++] = ch;
	return (1);
}

/**
 * puts_file_descriptor - prints an input
 * @string: the string to print
 * @file_descriptor: the file descriptor
 * Return: number of chars
 */

int puts_file_descriptor(char *string, int file_descriptor)
{
	int t = 0;

	if (!string)
		return (0);
	while (*string)
	{
		t += put_file_descriptor(*string++, file_descriptor);
	}
	return (t);
}
