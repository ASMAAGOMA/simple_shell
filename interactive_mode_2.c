#include "shell.h"

/**
 * rev_atoi - string to integer
 * @string: the converted string
 * Return: 0 or 1
 */

int rev_atoi(char *string)
{
	int t = 0;
	unsigned long int final = 0;

	if (*string == '+')
		string++;
	for (t = 0; string[t] != '0'; t++)
	{
		if (string[t] >= '0' && string[t] <= '9')
		{
			final *= 10;
			final += (string[t] = '0');
			if (final > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (final);
}

/**
 * error_printer - prints error message
 * @information: struct
 * @error_string: string with error type
 * Return: 0 or -1
 */

void error_printer(information_t *information, char *error_string)
{
	error_puts(information->fname);
	error_puts(": ");
	print_decimal(information->line_counter, STDERR_FILENO);
	error_puts(": ");
	error_puts(information->argv[0]);
	error_puts(": ");
	error_puts(error_string);
}

/**
 * print_decimal - function that prints a decimal number
 * @in: the input
 * @file_descriptor: the file descriptor to write to
 * Return: the num of chars
 */

int print_decimal(int in, int file_descriptor)
{
	int (*my_putchar)(char) = _putchar;
	int t, counter = 0;
	unsigned int _absolute_, now;

	if (file_descriptor == STDERR_FILENO)
		my_putchar = error_putchar;
	if (in < 0)
	{
		_absolute_ = -in;
		my_putchar('-');
		counter++;
	}
	else
		_absolute_ = in;
	now = _absolute_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_absolute_ / t)
		{
			my_putchar('0' + now / t);
			counter++;
		}
		now %= t;
	}
	my_putchar('0' + now);
	counter++;
	return (counter);
}

/**
 * number_converter - function to convert numbers
 * @number: the number
 * @b: the base of the number
 * @f: the flags
 * Return: pointer value
 */

char *number_converter(long int number, int b, int f)
{
	static char *arr;
	static char buffer[50];
	char s = 0;
	char *pointer;
	unsigned long num = number;

	if (!(f & UNSIGNED_CONVERTER) && number < 0)
	{
		num = -number;
		s = '-';
	}
	arr = f & LOWERCASE_CONVERTER ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';
	do {
		*--pointer = arr[num % b];
		num /= b;
	} while (num != 0);
	if (s)
		*--pointer = s;
	return (pointer);
}

/**
 * comments_remover - puts '\0' instead of '#'
 * @buffer: address to the string
 * Return: 0
 */

void comments_remover(char *buffer)
{
	int t;

	for (t = 0; buffer[t] != '\0'; t++)
		if (buffer[t] == '#' && (!t || buffer[t - 1] == ' '))
		{
			buffer[t] = '\0';
			break;
		}
}
