#include "shell.h"

/**
 * main - Entry point
 * Return: 0 success
 */
int main(void)
{
	int argc = 0;
	char **argv = NULL;
	char *line = NULL;
	size_t len = 0;
	int read_len;

	prompt();
	while ((read_len = getline(&line, &len, stdin)) != -1)
	{
		/*Exit on Ctrl+D*/
		if (line[0] == EOF)
			break;

		/*Replace '\n' with null-terminator*/
		if (line[read_len - 1] == '\n')
			line[read_len - 1] = '\0';

		argc = getArgv(line, &argv);
		if ((_strcmp(argv[0], "exit") == 0) && argv[1] != NULL)
		{
			int exit_code = atoi(argv[1]);
			freeArgv(&argv);
			free(line);
			exit(exit_code);
		}
		else if (_strcmp(argv[0], "exit") == 0)
		{
			break;
		}
		else if (_strcmp(argv[0], "env") == 0)
		{
			printenv();
		}
		else if (argc > 0)
		{
			executeCommand(argv);
		}
		freeArgv(&argv);

		/*Print the next prompt*/
		prompt();
	}
	free(line);
	return (0);
}
