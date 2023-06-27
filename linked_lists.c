#include "shell.h"

/**
 * add_node_start - adds node to the start of the list
 * @h: the hesd of the list
 * @string: the string
 * @n: node index
 * Return: the vaalue of new
 */

list_t *add_node_start(list_t **h, const char *string, int n)
{
	list_t *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	memory_setting((void *)new, 0, sizeof(list_t));
	new->number = n;
	if (string)
	{
		new->string = string_duplication(string);
		if (!new->string)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * add_node_at_end - adds node at the end of the list
 * @h: the hesd of the list
 * @string: the string
 * @n: node index
 * Return: the value of t
 */

list_t *add_node_at_end(list_t **h, const char *string, int n)
{
	list_t *new, *no;

	if (!h)
		return (NULL);
	no = *h;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	memory_setting((void *)new, 0, sizeof(list_t));
	new->number = n;
	if (string)
	{
		new->string = string_duplication(string);
		if (!new->string)
		{
			free(new);
			return (NULL);
		}
	}
	if (no)
	{
		while (no->next)
			no = no->next;
		no->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * print_string_list - prints the string element of the linked list
 * @head: the head of the list
 * Return: t
 */

int print_string_list(const list_t *head)
{
	size_t t = 0;

	while (head)
	{
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		t++;
	}
	return (t);
}
/**
 * delete_node_index - deletes node at specific index
 * @h: the head of the list
 * @i: the node ondex
 * Return: 0
 */

int delete_node_index(list_t **h, unsigned int i)
{
	list_t *n, *prev_n;
	unsigned int t = 0;

	if (!h || !*h)
		return (0);
	if (!i)
	{
		n = *h;
		*h = (*h)->next;
		free(n->string);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (t == i)
		{
			prev_n->next = n->next;
			free(n->string);
			free(n);
			return (1);
		}
		t++;
		prev_n = n;
		n = n->next;
	}
	return (0);
}

/**
 * list_free - frees nodes of the list
 * @h_pointer: pointer to the head
 * Return: nothing
 */

void list_free(list_t **h_pointer)
{
	list_t *n, *next_n, *h;

	if (!h_pointer || !*h_pointer)
		return;
	h = *h_pointer;
	n = h;
	while (n)
	{
		next_n = n->next;
		free(n->string);
		free(n);
		n = next_n;
	}
	*h_pointer = NULL;
}
