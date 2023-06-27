#include "shell.h"

/**
 * list_length - calculates the length of linked list
 * @head: the head of the list
 * Return: t
 */

size_t list_length(const list_t *head)
{
	size_t t = 0;

	while (head)
	{
		head = head->next;
		t++;
	}
	return (t);
}

/**
 * list_strings - arrayof strings ofthe list
 * @h: head of the list
 * Return: strings
 */

char **list_strings(list_t *h)
{
	list_t *n = h;
	size_t t = list_length(h), i;
	char **strings;
	char *strs;

	if (!h || !t)
		return (NULL);
	strings = malloc(sizeof(char *) * (t + 1));
	if (!strings)
		return (NULL);
	for (t = 0; n; n = n->next, t++)
	{
		strs = malloc(string_length(n->string) + 1);
		if (!strs)
		{
			for (i = 0; i < t; i++)
				strings[t] = strs;
		}
		strs = string_copy(strs, n->string);
		strings[t] = strs;
	}
	strings[t] = NULL;
	return (strings);
}

/**
 * list_printer - print the elements of the list
 * @head: the head of the list
 * Return: t
 */

size_t list_printer(const list_t *head)
{
	size_t t = 0;

	while (head)
	{
		_puts(number_converter(head->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		t++;
	}
	return (t);
}
/**
 * starts_the_node - fuction to get the starting node of the list
 * @n: n
 * @pre: prefix
 * @next_c: next char
 * Return: n
 */
list_t *starts_the_node(list_t *n, char *pre, char next_c)
{
	char *m = NULL;

	while (n)
	{
		m = starting(n->string, pre);
		if (m && ((next_c == -1) || (*m == next_c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * getting_index - gets inex of the node
 * @h: head
 * @n: the node
 * Return: t
 */

ssize_t getting_index(list_t *h, list_t *n)
{
	size_t t = 0;

	while (h)
	{
		if (h == n)
			return (t);
		h = h->next;
		t++;
	}
	return (-1);
}
