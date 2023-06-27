#include "shell.h"

/**
 * memory_setting - buts a constant byte in memory
 * @m: memory area
 * @byte: the bytes that m is filled with
 * @amount: amount of bytes
 * Return: pointer to memory area
 */

char *memory_setting(char *m, char byte, unsigned int amount)
{
	unsigned int t;

	for (t = 0; t < amount; t++)
		m[t] = byte;
	return (m);
}

/**
 * string_free - frees a string of strings
 * @ss: the string of strings
 */
void string_free(char **ss)
{
	char **s = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(s);
}

/**
 * memory_reallocation - reallocates memory
 * @pointer: pointes to the prev mallocated memory
 * @old_s: size of prev block
 * @new_s: size of new block
 * Return: pointes to the old block
 */

void *memory_reallocation(void *pointer, unsigned int old_s,
	unsigned int new_s)
{
	char *m;

	if (!pointer)
		return (malloc(new_s));
	if (!new_s)
		return (free(pointer), NULL);
	if (new_s == old_s)
		return (pointer);
	m = malloc(new_s);
	if (!pointer)
		return (NULL);
	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		m[old_s] = ((char *)pointer)[old_s];
	free(pointer);
	return (m);
}

/**
 * pointer_free - function that frees a pointer
 * @pointer: pointer to be freed
 * Return: 0or1
 */

int pointer_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
