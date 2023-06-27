#include "shell.h"

/**
 * main - entrypoint
 * @ac: argument count
 * @av: argument vector
 * Return: 0 or 1
 */

int main(int ac, char **av)
{
	information_t information[] = { INFORMATION_INIT };
	int file_discriptor = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (file_discriptor)
	: "r" (file_discriptor));
	if (ac == 2)
	{
		file_discriptor = open(av[1], O_RDONLY);
		if (file_discriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(av[0]);
				error_puts(": 0: Can't open ");
				error_puts(av[1]);
				error_putchar('\n');
				error_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->read_file_discriptor = file_discriptor;
	}
	environ_population(information);
	his_read(information);
	my_hsh(information, av);
	return (EXIT_SUCCESS);
}
