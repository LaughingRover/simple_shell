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
		exit(commandline_mode(&argc, &argv, &env));
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
 * command_line mode - Run shell in command line mode
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Description: Takes a file and run commands in it one line at a time
 *
 * Return: 0 if successful
 */
int commandline_mode(int *argc UNUSED, char ***argv UNUSED, char ***env UNUSED)
{
	/*path to file containing commands*/
	char *file_path UNUSED = (*argv)[1];

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
	if ((_strcmp((*argv)[0], "exit") == 0) && (*argv)[1] != NULL)
	{
		int exit_code = atoi((*argv)[1]);

		free_argv(argv);
		free(line);
		exit(exit_code);
	}
	else if (_strcmp((*argv)[0], "exit") == 0)
		exit(0);
	else if (_strcmp((*argv)[0], "env") == 0)
		printenv();
	else if (_strcmp((*argv)[0], "cd") == 0)
		change_working_dir(*argv);

	else if (_strcmp((*argv)[0], "setenv") == 0)
		modifyenv(*argv);

	else if (_strcmp((*argv)[0], "unsetenv") == 0)
		modifyenv(*argv);

	else
		execute_command(*argv);

	free(line);
}

