#include "shell.h"

/**
 * exit_shell - shell_exit
 * @information: info
 * Return: 1 or -2
 */

int exit_shell(information_t *information)
{
	int ex;

	if (information->argv[1])
	{
		ex = rev_atoi(information->argv[1]);
		if (ex == -1)
		{
			information->status = 2;
			error_printer(information, "Illegal number: ");
			error_puts(information->argv[1]);
			error_putchar('\n');
			return (1);
		}
		information->error_number = rev_atoi(information->argv[1]);
		return (-2);
	}
	information->error_number = -1;
	return (-2);
}

/**
 * change_directory - change the current directory
 * @i: info
 * Return: o
 */
int change_directory(information_t *i)
{
	char buf[1024], *n = getcwd(buf, 1024), *d;
	int r;

	if (!n)
		_puts("TODO: getcwd failure emsg here<<\n");
	if (!i->argv[1])
	{
		d = getting_environment(i, "HOME=");
		if (!d)
			r = chdir((d = getting_environment(i, "PWD=")) ? d : "/");
		else
			r = chdir(d);

	}
	else if (string_cmp(i->argv[1], "-") == 0)
	{
		if (!getting_environment(i, "OLDPWD="))
		{
			_puts(n);
			_putchar('\n');
			return (1);
		}
		_puts(getting_environment(i, "OLDPWD=")), _putchar('\n');
		r = chdir((d = getting_environment(i, "OLDPWD=")) ? d : "/");
	}
	else
		r = chdir(i->argv[1]);
	if (r == -1)
	{
		error_printer(i, "can't cd to");
		error_puts(i->argv[1]), error_putchar('\n');
	}
	else
	{
		setting_the_environ(i, "OLDPWD",
		getting_environment(i, "PWD="));
		setting_the_environ(i, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * the_h - gets the cuurnt directory changed
 * @information: info
 * Return: 0
 */

int the_h(information_t *information)
{
	char **ar;

	ar = information->argv;
	_puts("help call works. function not yet implemented \n");
	if (0)
		_puts(*ar);
	return (0);
}
