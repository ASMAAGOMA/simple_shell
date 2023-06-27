#include "shell.h"

/**
 * environment_getting - gets string array copy
 * @information: info
 * Return: 0
 */

char **environment_getting(information_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_strings(information->environment);
		information->env_changed = 0;
	}
	return (information->environ);
}

/**
 * my_unsetting_environ - remove the variable
 * @information: info
 * @variable: variable
 * Return: the var
 */

int my_unsetting_environ(information_t *information, char *variable)
{
	list_t *n = information->environment;
	size_t t = 0;
	char *m;

	if (!n || !variable)
		return (0);
	while (n)
	{
		m = starting(n->string, variable);
		if (m && *m == '=')
		{
			information->env_changed =
			delete_node_index(&(information->environment), t);
			t = 0;
			n = information->environment;
			continue;
		}
		n = n->next;
		t++;
	}
	return (information->env_changed);
}

/**
 * setting_the_environ - env var initialization
 * @information: information
 * @variable: variable
 * @v: var
 * Return: the var
 */

int setting_the_environ(information_t *information, char *variable, char *v)
{
	char *buffer = NULL;
	list_t *n;
	char *m;

	if (!variable || !v)
		return (0);
	buffer = malloc(string_length(variable) + string_length(v) + 2);
	if (!buffer)
		return (1);
	string_copy(buffer, variable);
	string_cat(buffer, "=");
	string_cat(buffer, v);
	n = information->environment;
	while (n)
	{
		m = starting(n->string, variable);
		if (m && *m == '=')
		{
			free(n->string);
			n->string = buffer;
			information->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_at_end(&(information->environment), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}
