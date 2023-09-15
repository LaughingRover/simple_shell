#include "shell.h"

#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#endif

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

		freeArgv(&argv);
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
	int read_len = getline(&line, &len, stdin);

	/*Exit on Ctrl+D (EOF)*/
	if (read_len == -1)
	{
		free(line);
		exit(0);
	}

	/*Replace '\n' with null-terminator*/
	if (line[read_len - 1] == '\n')
		line[read_len - 1] = '\0';

	*argc = getArgv(line, argv);
	if (*argc > 0)
	{
		if ((_strcmp((*argv)[0], "exit") == 0) && (*argv)[1] != NULL)
		{
			int exit_code = atoi((*argv)[1]);

			freeArgv(argv);
			free(line);
			exit(exit_code);
		}

		if (_strcmp((*argv)[0], "exit") == 0)
			exit(0);

		if (_strcmp((*argv)[0], "env") == 0)
			printenv();

		else
			executeCommand(*argv);
	}
	free(line);
}
