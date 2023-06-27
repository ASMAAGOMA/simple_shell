#include "shell.h"

/**
 * buf_in - commands that are chained
 * @information: information
 * @buffer: buffer
 * @l: length
 * Return: t
 */

ssize_t buf_in(information_t *information, char **buffer, size_t *l)
{
	ssize_t t = 0;
	size_t le = 0;

	if (!*l)
	{
		free(buffer);
		*buffer = NULL;
		signal(SIGINT, s_h);
#if USE_GETLINE
		t = getline(buffer, &le, stdin);
#else
		t = g_t(information, buffer, &le);
#endif
		if (t > 0)
		{
			if ((*buffer)[t - 1] == '\n')
			{
				(*buffer)[t - 1] = '\0';
				t--;
			}
			information->line_count_flag = 1;
			comments_remover(*buffer);
			building_list(information, *buffer, information->history_count++);
			/*if (string_char(*buffer, ';')) is this a chain*/
			{
				*l = t;
				information->command_buffer = buffer;
			}
		}
	}
	return (t);
}

/**
 * s_h - control c blocker
 * @s_n: the signl of the number
 * Return: nothing
 */

void s_h(__attribute__((unused))int s_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * in_getting - new line
 * @information: information
 * Return: m
 */

ssize_t in_getting(information_t *information)
{
	static char *buffer;
	static size_t t, i, l;
	ssize_t m = 0;
	char **buf = &(information->arg), *b;

	_putchar(BUFFER_FLUSH);
	m = buf_in(information, &buffer, &l);
	if (m == -1)
		return (-1);
	if (l)
	{
		i = t;
		b = buffer + t;
		ch_checker(information, buffer, &i, t, l);
		while (i < l)
		{
			if (have_ch(information, buffer, &i))
				break;
			i++;
		}
		t = i + 1;
		if (t >= l)
		{
			t = l = 0;
			information->command_buffer_type = COMMAND_NORM;
		}
		*buf = b;
		return (string_length(b));
	}
	*buf = buffer;
	return (m);
}

/**
 * buffer_r - buffer reader
 * @information: info
 * @buffer: buffer
 * @t: the size
 * Return: m
 */

ssize_t buffer_r(information_t *information, char *buffer, size_t *t)
{
	ssize_t m = 0;

	if (*t)
		return (0);
	m = read(information->read_file_discriptor, buffer, READ_BUFFER_SIZE);
	if (m >= 0)
		*t = m;
	return (m);
}

/**
 * g_t - neXt line
 * @information: information
 * @pointer: pointer
 * @l: length
 * Return: a
 */

int g_t(information_t *information, char **pointer, size_t *l)
{
	static char buffer[1024];
	static size_t t, length;
	size_t h;
	ssize_t m = 0, a = 0;
	char *b = NULL, *n = NULL, *s;

	b = *pointer;
	if (b && l)
		a = *l;
	if (t == length)
		t = length = 0;
	m = buffer_r(information, buffer, &length);
	if (m == -1 || (m == 0 && length == 0))
		return (-1);
	s = string_char(buffer + t, '\n');
	h = s ? 1 + (unsigned int)(s - buffer) : length;
	n = memory_reallocation(b, a, a ? a + h : h + 1);
	if (!n)
		return (b ? free(b), -1 : -1);
	if (a)
		string_n_cat(n, buffer + t, h - t);
	else
		string_n_copy(n, buffer + t, h - t + 1);
	a += h - t;
	t = h;
	b = n;
	if (l)
		*l = a;
	*pointer = b;
	return (a);
}
