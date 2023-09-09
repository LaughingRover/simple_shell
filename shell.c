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
	int read;

	prompt();
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		/*Exit on Ctrl+D*/
		if (line[0] == EOF)
			break;

		/*Replace '\n' with null-terminator*/
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		argc = getArgv(line, &argv);
		if (argc > 0)
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
