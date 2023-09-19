#include "shell.h"

/**
 * change_working_dir - changes working directory
 * @argv: argument variables
 *
 * Return: void
 */
void change_working_dir(char **argv)
{
	/**
	 * TODO:
	 * - Get home from env
	 * - Add more features
	 */
	const char *HOME = "/home/vagrant";

	if (argv[1] == NULL)
		chdir(HOME);
	else
		return;
}
