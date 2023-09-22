#include "shell.h"

/**
 * handle_signal - handle signals
 * @sigint: signal number
 */
void handle_signal(int sigint)
{
	prompt(sigint);
	if (sigint == 2)
	{
		errno = 130;
	}
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 success
 */
int main(int argc, char **argv)
{
	signal(SIGINT, handle_signal);

	if (argc > 1)
	{
		exit(execute_commands_from_file(&argc, argv));
	}

	while (prompt(0))
	{
		argc = get_argv(&argv);
		if (argc > 0)
		{
			argv[argc] = NULL;
			run_command(argv);
			free_argv(argv);
		}
	}
	return (0);
}

/**
 * execute_commands_from_file - Execute commands from a file
 * @argc: argument count
 * @argv: argument vector
 *
 * Description: Reads commands from the specified file and executes them
 *
 * Return: 0 if successful, -1 on error
 */
int execute_commands_from_file(int *argc UNUSED, char **argv UNUSED)
{
	/*
	char *filename = argv[1];
	const char *delim = NULL;
	ssize_t bytes_read = 0;
	size_t n = BUFFER_SIZE;
	char *lineptr = malloc(n);
	int fd = open(filename, O_RDONLY);

	if (fd == -1 || lineptr == NULL)
	{
		free(lineptr);
		return (-1);
	}

	while ((bytes_read = readline(&lineptr, &n, fd)) != EOF)
	{
		delim = (_strchr(lineptr, ';')) ? ";" : " ";
		*argc = get_argv(lineptr, &argv, delim);

		if (!(*argc > 1 && run_command(argv) != -1))
		{
			free_argv(argv), free(lineptr), close(fd);
			return (-1);
		}
		_memset(lineptr, 0, n);
		free_argv(argv);
	}
	free(lineptr);
	close(fd);
	*/
	return (0);
}

/**
 * run_command - this function is responsible for
 * directing the flow of execution
 * @argv: argument vector
 *
 * Return: 0 if succesful and -1 if unsuccessful
 */
int run_command(char **argv)
{
	get_builtin execute_builtin;
	int run_status;

	execute_builtin = handle_builtin_func(argv[0]);
	if (execute_builtin)
		run_status = execute_builtin(argv);
	else
		run_status = execute_command(argv);

	return (run_status);
}
