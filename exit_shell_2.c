#include "shell.h"

/**
 * history_display - display the history
 * @information: the info
 * Return: 0
 */

int history_display(information_t *information)
{
	list_printer(information->history);
	return (0);
}

/**
 * alias_unsetting - alias removing
 * @information: the info
 * @string: the string
 * Return: 0 or 1
 */

int alias_unsetting(information_t *information, char *string)
{
	char *b, s;
	int r;

	b = string_char(string, '=');
	if (!b)
		return (1);
	s = *b;
	*b = 0;
	r = delete_node_index(&(information->alias),
	getting_index(information->alias,
	starts_the_node(information->alias, string, -1)));
	*b = s;
	return (r);
}

/**
 * alias_setting - alias setting
 * @information: the info
 * @string: the string
 * Return: 0 or 1
 */

int alias_setting(information_t *information, char *string)
{
	char *b;

	b = string_char(string, '=');
	if (!b)
		return (1);
	if (!*b++)
		return (alias_unsetting(information, string));
	alias_unsetting(information, string);
	return (add_node_at_end(&(information->alias), string, 0) == NULL);
}

/**
 * alias_printer - prints an alias
 * @n: node
 * Return: 0 or 1
 */

int alias_printer(list_t *n)
{
	char *b = NULL, *c = NULL;

	if (n)
	{
		b = string_char(n->string, '=');
		for (c = n->string; c <= b; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mimic_alias - mimics the alias
 * @information: information
 * Return: 0
 */

int mimic_alias(information_t *information)
{
	int t = 0;
	char *b = NULL;
	list_t *n = NULL;

	if (information->argc == 1)
	{
		n = information->alias;
		while (n)
		{
			alias_printer(n);
			n = n->next;
		}
		return (0);
	}
	for (t = 1; information->argv[t]; t++)
	{
		b = string_char(information->argv[t], '=');
		if (b)
			alias_setting(information, information->argv[t]);
		else
			alias_printer(starts_the_node(information->alias,
			information->argv[t], '='));
	}
	return (0);
}
