#include "shell.h"

/**
 * information_clearing - information_t struct initialization
 * @information: address to struct
 */

void information_clearing(information_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * information_setting - information_t struct initialization
 * @information: address to struct
 * @av: vector
 */

void information_setting(information_t *information, char **av)
{
	int t = 0;

	information->fname = av[0];

	if (information->arg)
	{
		information->argv = string_split(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = string_duplication(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (t = 0; information->argv && information->argv[t]; t++)
			;
		information->argc = t;
		alias_replacement(information);
		variable_replacement(information);
	}
}

/**
 * freedom - free struct
 * @information: information
 * @e: all fields
 */

void freedom(information_t *information, int e)
{
	string_free(information->argv);
	information->argv = NULL;
	information->path = NULL;

	if (e)
	{
		if (information->command_buffer)
			free(information->arg);
		if (information->environment)
			list_free(&(information->environment));
		if (information->history)
			list_free(&(information->history));
		if (information->alias)
			list_free(&(information->alias));
		string_free(information->environ);
		information->environ = NULL;
		pointer_free((void **)information->command_buffer);
		if (information->read_file_discriptor)
			close(information->read_file_discriptor);
		_putchar(BUFFER_FLUSH);
	}
}
