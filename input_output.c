#include "shell.h"

/**
 * his_file - get history file
 * @information: information
 * Return: buffer
 */

char *his_file(information_t *information)
{
	char *buffer, *d;

	d = getting_environment(information, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_length(d) +
				string_length(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	string_copy(buffer, d);
	string_cat(buffer, "/");
	string_cat(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * his_write - for creating files
 * @information: information
 * Return: 1 or -1
 */

int his_write(information_t *information)
{
	ssize_t file_discriptor;
	char *fn = his_file(information);
	list_t *n = NULL;

	if (!fn)
		return (-1);
	file_discriptor = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (file_discriptor == -1)
		return (-1);
	for (n = information->history; n; n = n->next)
	{
		puts_file_descriptor(n->string, file_discriptor);
		put_file_descriptor('\n', file_discriptor);
	}
	put_file_descriptor(BUFFER_FLUSH, file_discriptor);
	close(file_discriptor);
	return (1);
}

/**
 * his_read - history reader
 * @information: information
 * Return: hisor0
 */

int his_read(information_t *information)
{
	int t, l = 0, lc = 0;
	ssize_t file_discriptor, rdl, file_size;
	struct stat st;
	char *buffer = NULL, *fn = his_file(information);

	if (!fn)
		return (0);
	file_discriptor = open(fn, O_RDONLY);
	free(fn);
	if (file_discriptor == -1)
		return (0);
	if (!fstat(file_discriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	rdl = read(file_discriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (rdl <= 0)
		return (free(buffer), 0);
	close(file_discriptor);
	for (t = 0; t < file_size; t++)
		if (buffer[t] == '\n')
		{
			buffer[t] = 0;
			building_list(information, buffer + l, lc++);
			l = t + 1;
		}
	if (l != t)
		building_list(information, buffer + l, lc++);
	free(buffer);
	information->history_count = lc;
	while (information->history_count-- >= HISTORY_MAXIMUM)
		delete_node_index(&(information->history), 0);
	renumbering(information);
	return (information->history_count);
}

/**
 * building_list - entry added to list
 * @information: information
 * @buffer: buffer
 * @lc: line pount
 * Return: 0
 */

int building_list(information_t *information, char *buffer, int lc)
{
	list_t *n = NULL;

	if (information->history)
		n = information->history;
	add_node_at_end(&n, buffer, lc);
	if (!information->history)
		information->history = n;
	return (0);
}

/**
 * renumbering - renumber the list
 * @information: information
 * Return: history_count
 */

int renumbering(information_t *information)
{
	list_t *n = information->history;
	int t = 0;

	while (n)
	{
		n->number = t++;
		n = n->next;
	}
	return (information->history_count = t);
}
