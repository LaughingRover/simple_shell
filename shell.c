#include "shell.h"

/**
 * main - Entry point
 * Return: 0 success, 1 failure
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
		/*Replace newline character with terminator '\0*/
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		argc = getArgv(line, &argv);
		if (argc < 0)
		{
			perror("Command failed");
		}
		executeCommand(argv);

		/*Print the next prompt*/
		prompt();
	}

	freeArgv(&argv);
	free(line);
	return (0);
}
