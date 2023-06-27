#include "shell.h"

/**
 * have_ch - checks if chain or not
 * @information: info
 * @buffer: the buffer
 * @possition: possition
 * Return: 0 or 1
 */

int have_ch(information_t *information, char *buffer, size_t *possition)
{
	size_t i = *possition;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		information->command_buffer_type = COMMAND_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		information->command_buffer_type = COMMAND_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		information->command_buffer_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*possition = i;
	return (1);
}

/**
 * ch_checker - continue chain
 * @information: info
 * @buffer: the buffer
 * @possition: possition
 * @t: first position
 * @l: buffer len
 * Return: nothing
 */

void ch_checker(information_t *information, char *buffer,
	size_t *possition, size_t t, size_t l)
{
	size_t p = *possition;

	if (information->command_buffer_type == COMMAND_AND)
	{
		if (information->status)
		{
			buffer[t] = 0;
			p = l;
		}
	}
	if (information->command_buffer_type == COMMAND_OR)
	{
		if (!information->status)
		{
			buffer[t] = 0;
			p = l;
		}
	}
	*possition = p;
}

/**
 * alias_replacement - alias replacement
 * @information: info
 * Return: 0 or 1
 */

int alias_replacement(information_t *information)
{
	int t;
	list_t *n;
	char *b;

	for (t = 0; t < 10; t++)
	{
		n = starts_the_node(information->alias, information->argv[0], '=');
		if (!n)
			return (0);
		free(information->argv[0]);
		b = string_char(n->string, '=');
		if (!b)
			return (0);
		information->argv[0] = b;
	}
	return (1);
}

/**
 * variable_replacement - variable replacement
 * @information: info
 * Return: 0 or 1
 */

int variable_replacement(information_t *information)
{
	int t = 0;
	list_t *n;

	for (t = 0; information->argv[t]; t++)
	{
		if (information->argv[t][0] != '$' || information->argv[t][1])
			continue;
		if (!string_cmp(information->argv[t], "$?"))
		{
			string_replacement(&(information->argv[t]),
			string_duplication(number_converter(information->status, 10, 0)));
			continue;
		}
		if (!string_cmp(information->argv[t], "$$"))
		{
			string_replacement(&(information->argv[t]),
			string_duplication(number_converter(getpid(), 10, 0)));
			continue;
		}
		n = starts_the_node(information->environment,
		&information->argv[t][1], '=');
		if (n)
		{
			string_replacement(&(information->argv[t]),
			string_duplication(string_char(n->string, '=') + 1));
			continue;
		}
		string_replacement(&(information->argv[t]), string_duplication(""));
	}
	return (0);
}

/**
 * string_replacement - string replacement
 * @o: old string
 * @n: new string
 * Return: 1 or 0
 */

int string_replacement(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
