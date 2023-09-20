#include "shell.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Return: 0 success
 */
int main(int argc, char **argv, char **env)
{
	(void)env;

	if (argc > 1)
	{
		exit(execute_commands_from_file(&argc, &argv));
	}

	while (1)
	{
		prompt();

		interactive_mode(&argc, &argv, &env);

		free_argv(&argv);
	}
	return (0);
}

/**
 * execute_commands_from_file - Execute commands from a file
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Description: Reads commands from the specified file and executes them
 *
 * Return: 0 if successful, -1 on error
 */
int execute_commands_from_file(int *argc, char ***argv)
{
	char *filename = (*argv)[1];
	int fd = open(filename, O_RDONLY);
	size_t n = BUFFER_SIZE;
	char *lineptr = malloc(n);

	if (fd == -1)
	{
		perror("Error opening file");
		free(lineptr);
		return (-1);
	}

	while (1)
	{
		ssize_t bytes_read = readline(&lineptr, &n, fd);
		printf("\nbytes_read: %ld\n", bytes_read);

		lineptr[bytes_read - 1] = '\0';

		if (bytes_read == -1)
		{
			perror("Error reading line from file");
			free(lineptr);
			close(fd);
			return (-1);
		}

		/*EOF reached*/
		if (bytes_read == 0)
			break;

		/*Tokenize command into argv*/
		*argc = get_argv(lineptr, argv);

		printf("lineptr: %s %s\n", (*argv)[0], (*argv)[1]);
		printf("argc: %d\n", *argc);

		/*Execute command*/
		if (!(*argc > 1 && run_command(argv) != -1))
		{
			free_argv(argv);
			free(lineptr);
			close(fd);
			return (-1);
		}

		free_argv(argv);
		lineptr[0] = '\0';
	}
	free(lineptr);
	close(fd);

	return (0);
}

/**
 * interactive_mode - Run shell in interactive mode
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Return: 0 success
 */
void interactive_mode(int *argc, char ***argv, char ***env UNUSED)
{
	char *line = NULL;
	size_t len = 0;
	int read_len = _getline(&line, &len, stdin);
	char newline = '\n';

	if (read_len == -1) /*Exit on Ctrl+D (EOF)*/
	{
		free(line);
		write(1, &newline, 1);
		exit(0);
	}
	if (line[read_len - 1] == '\n') /*Replace '\n' with null-terminator*/
		line[read_len - 1] = '\0';

	*argc = get_argv(line, argv);
	if (*argc < 1)
	{
		free(line);
		return;
	}
	run_command(argv);
	free(line);
}

/**
 * run_command - this function is responsible for
 * directing the flow of execution
 * @argv: argument vector
 *
 * Return: -1 if unsuccesful
 */
int run_command(char ***argv)
{
	get_builtin execute_builtin;
	int run_status;

	execute_builtin = handle_builtin_func((*argv)[0]);
	if (execute_builtin)
		run_status = execute_builtin(argv);
	else
		run_status = execute_command(*argv);

	return (run_status);
}
