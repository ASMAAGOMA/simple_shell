#include "shell.h"

/**
 * the_environment - function to print the environment
 * @information: information
 * Return: 0
 */

int the_environment(information_t *information)
{
	print_string_list(information->environment);
	return (0);
}

/**
 * getting_environment - function to get the environment
 * @information: information
 * @na: name
 * Return: b
 */

char *getting_environment(information_t *information, char *na)
{
	list_t *n = information->environment;
	char *b;

	while (n)
	{
		b = starting(n->string, na);
		if (b && *b)
			return (b);
		n = n->next;
	}
	return (NULL);
}

/**
 * setting_environ - sets the environment
 * @information: information
 * Return: 0
 */

int setting_environ(information_t *information)
{
	if (information->argc != 3)
	{
		error_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setting_the_environ(information, information->argv[1],
	information->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetting_environ - unsetting the environ
 * @information: information
 * Return: 0
 */

int unsetting_environ(information_t *information)
{
	int t;

	if (information->argc == 1)
	{
		error_puts("Too few arguements.\n");
		return (1);
	}
	for (t = 1; t <= information->argc; t++)
		my_unsetting_environ(information, information->argv[t]);
	return (0);
}

/**
 * environ_population - function to populate the environ
 * @information: information
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

