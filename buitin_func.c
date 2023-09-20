#include "shell.h"

/**
 * change_working_dir - changes working directory
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int change_working_dir(char ***argv)
{
	/**
	 * TODO:
	 * - Get home from env
	 * - Add more features
	 */
	const char *HOME = "/home/vagrant";

	if ((*argv)[1] == NULL)
	{
		chdir(HOME);
		return (0);
	}
	else
	{
		return (-1);
	}
}

/**
 * printenv - prints environment variable
 * @argv: argument vector
 *
 * Return: 0 if successful
 */
int printenv(char ***argv)
{
	int i = 0;

	(void)argv;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}

/**
 * exit_simple_shell - exit shell
 * @argv: argument vector
 *
 * Return: 0 on exit and status if exit code is given
 */
int exit_simple_shell(char ***argv)
{
	char *exit_code = (*argv)[1];

	if (!exit_code)
	{
		exit(0);
	}
	else
	{
		int code = atoi(exit_code);
		free_argv(argv);
		/**
		 * TODO: Free line here
		 */
		exit(code);
	}
	return (0);
}

/**
 * modifyenv - modifies current environment using setenv or unsetenv
 * @argv: argument vector
 *
 * Return: 0 if successful
 */
int modifyenv(char ***argv)
{
	char *command = (*argv)[0];
	int result;

	if (_strcmp(command, "setenv") == 0 &&
	    ((*argv)[1] != NULL) && ((*argv)[2] != NULL))
	{
		char *name = (*argv)[1];
		char *value = (*argv)[2];

		result = _setenv(name, value, 1);

		return (result);
	}

	if (_strcmp(command, "unsetenv") == 0 && ((*argv)[1] != NULL))
	{
		char *name = (*argv)[1];

		result = _unsetenv(name);

		return (result);
	}

	perror("Error: Environment not modified");
	return (-1);
}
