#include "shell.h"

/**
 * my_hsh - the hsh fun
 * @information: info
 * @vector: vector
 * Return: 0 or 1
 */

int my_hsh(information_t *information, char **vector)
{
	ssize_t m = 0;
	int b_r = 0;

	while (m != -1 && b_r != -2)
	{
		information_clearing(information);
		if (is_interact(information))
			_puts("$ ");
		error_putchar(BUFFER_FLUSH);
		m = in_getting(information);
		if (m != -1)
		{
			information_setting(information, vector);
			b_r = bi_finder(information);
			if (b_r == -1)
				command_finder(information);
		}
		else if (is_interact(information))
			_putchar('\n');
		freedom(information, 0);
	}
	his_write(information);
	freedom(information, 1);
	if (!is_interact(information) && information->status)
		exit(information->status);
	if (b_r == -2)
	{
		if (information->error_number == -1)
			exit(information->status);
		exit(information->error_number);
	}
	return (b_r);
}

/**
 * bi_finder - finds command
 * @information: information
 * Return:-1 or 0 or 1 or -2
 */

int bi_finder(information_t *information)
{
	int t, b_r = -1;
	builtins_taple builtinpart[] = {
		{"exit", exit_shell},
		{"env", the_environment},
		{"help", the_h},
		{"history", history_display},
		{"setenv", setting_environ},
		{"unsetenv", unsetting_environ},
		{"cd", change_directory},
		{"alias", mimic_alias},
		{NULL, NULL}
	};

	for (t = 0; builtinpart[t].type; t++)
	{
		if (string_cmp(information->argv[0], builtinpart[t].type) == 0)
		{
			information->line_counter++;
			b_r = builtinpart[t].function(information);
			break;
		}
	}
			return (b_r);
}

/**
 * command_finder - finds the command
 * @information: information
 * Return: nothing
 */

void command_finder(information_t *information)
{
	char *p = NULL;
	int t, j;

	information->path = information->argv[0];
	if (information->line_count_flag == 1)
	{
		information->line_counter++;
		information->line_count_flag = 0;
	}
	for (t = 0, j = 0; information->arg[t]; t++)
		if (!is_delimeter(information->arg[t], " \t\n"))
			j++;
	if (!j)
		return;
	p = p_finder(information, getting_environment(information, "PATH="),
			information->argv[0]);
	if (p)
	{
		information->path = p;
		command_f(information);
	}
	else
	{
		if ((is_interact(information) || getting_environment(information, "PATH=")
		|| information->argv[0][0] == '/')
		&& executable_command(information, information->argv[0]))
			command_f(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			error_printer(information, "not found\n");
		}
	}
}

/**
 * command_f - executable fork
 * @information: information
 * Return: nothing
 */

void command_f(information_t *information)
{
	pid_t c_p;

	c_p = fork();
	if (c_p == -1)
	{
		perror("Error:");
		return;
	}
	if (c_p == 0)
	{
		if (execve(information->path, information->argv,
		environment_getting(information)) == -1)
		{
			freedom(information, 1);
			if (errno == EACCES)
				exit(124);
			exit(1);
		}
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				error_printer(information, "Permission denied\n");
		}
	}
}
