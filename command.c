#include "shell.h"

/**
 * executable_command - checks if executable command
 * @information: information
 * @p: the path
 * Return: 1 or 0
 */

int executable_command(information_t *information, char *p)
{
	struct stat st;

	(void)information;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * chars_duplication - chars duplication
 * @p: string of the path
 * @s: first index
 * @e: last index
 * Return: buffer
 */

char *chars_duplication(char *p, int s, int e)
{
	static char buffer[1024];
	int t = 0, j = 0;

	for (j = 0, t = s; t < e; t++)
		if (p[t] != ':')
			buffer[j++] = p[t];
	buffer[j] = 0;
	return (buffer);
}

/**
 * p_finder - finds the path
 * @information: information
 * @ps: path string
 * @command: the command
 * Return: null or p
 */

char *p_finder(information_t *information, char *ps, char *command)
{
	int t = 0, c_p = 0;
	char *p;

	if (!ps)
		return (NULL);
	if ((string_length(command) > 2) && starting(command, "./"))
	{
		if (executable_command(information, command))
			return (command);
	}
	while (1)
	{
		if (!ps[t] || ps[t] == ':')
		{
			p = chars_duplication(ps, c_p, t);
			if (!*p)
				string_cat(p, command);
			else
			{
				string_cat(p, "/");
				string_cat(p, command);
			}
			if (executable_command(information, p))
				return (p);
			if (!ps[t])
				break;
			c_p = t;
		}
		t++;
	}
	return (NULL);
}
