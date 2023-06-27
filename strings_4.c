#include "shell.h"

/**
 * string_split - function that splits the string
 * @string: the string to be separated
 * @delimeter: the delimeters
 * Return: thev value ofm
 */
char **string_split(char *string, char *delimeter)
{
	int i, j, l, s = 0, num = 0;
	char **m;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!is_delimeter(string[i], delimeter) &&
		(is_delimeter(string[i + 1], delimeter) || !string[i + 1]))
			num++;
	if (num == 0)
		return (NULL);
	m = malloc((1 + num) * sizeof(char *));
	if (!m)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delimeter(string[i], delimeter))
			i++;
		l = 0;
		while (!is_delimeter(string[i + l], delimeter) &&
		string[i + l])
			l++;
		m[j] = malloc((l + 1) * sizeof(char));
		if (!m[j])
		{
			for (l = 0; l < j; l++)
				free(m[l]);
			free(m);
			return (NULL);
		}
		for (s = 0; s < l; s++)
			m[j][s] = string[i++];
		m[j][s] = 0;
	}
	m[j] = NULL;
	return (m);
}

/**
 * string_split2 - function to split the string into chars
 * @string: the string
 * @delimeter: the delimeters
 * Return: m
 */
char **string_split2(char *string, char delimeter)
{
	int i = 0, j, l = 0, s, num = 0;
	char **m;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != delimeter && string[i + 1] == delimeter) ||
		(string[i] != delimeter && !string[i + 1]) || string[i + 1] == delimeter)
			num++;
	if (num == 0)
		return (NULL);
	m = malloc((1 + num) * sizeof(char *));
	if (!m)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (string[i] == delimeter && string[i] != delimeter)
			i++;
		l = 0;
		while (string[i + l] != delimeter && string[i + l] &&
		string[i + l] != delimeter)
			l++;
		m[j] = malloc((l + 1) * sizeof(char));
		if (!m[j])
		{
			for (l = 0; l < j; l++)
				free(m[l]);
			free(m);
			return (NULL);
		}
		for (s = 0; s < l; s++)
			m[j][s] = string[i++];
		m[j][s] = 0;
	}
	m[j] = NULL;
	return (m);
}
