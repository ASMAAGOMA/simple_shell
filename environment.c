#include "shell.h"

/**
 * the_environment - print the environment
 * @information: info
 * Return: 0
 */

int the_environment(information_t *information)
{
	print_string_list(information->environment);
	return (0);
}

/**
 * getting_environment - gets the value of environment
 * @information: info
 * @na: name
 * Return: j
 */

char *getting_environment(information_t *information, char *na)
{
	list_t *n = information->environment;
	char *j;

	while (n)
	{
		j = starting(n->string, na);
		if (j && *j)
			return (j);
		n = n->next;
	}
	return (NULL);
}

/**
 * setting_environ - environment variable initialization
 * @information: info
 * Return: 0
 */

int setting_environ(information_t *information)
{
	if (information->argc != 3)
	{
		error_puts("INcorrect number of arguments\n");
		return (1);
	}
	if (setting_the_environ(information, information->argv[1],
				information->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetting_environ - remove environment
 * @information: info
 * Return: o
 */

int unsetting_environ(information_t *information)
{
	int t;

	if (information->argc == 1)
	{
		error_puts("Too few arguments.\n");
		return (1);
	}
	for (t = 1; t < information->argc; t++)
		my_unsetting_environ(information, information->argv[t]);
	return (0);
}

/**
 * environ_population - populates environment
 * @information: info
 * Return: 0
 */

int environ_population(information_t *information)
{
	list_t *n = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_at_end(&n, environ[t], 0);
	information->environment = n;
	return (0);
}
