#include "shell.h"

/**
 * executeCommand - executes a command with arguments
 * @argv: array of command and arguments
 *
 * Return: 0 on success, 1 on failure
 */
int executeCommand(char **argv)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		return (-1);
	}

	if (child_pid == 0)
	{
		char *cmd = argv[0];
		char *envp[] = {NULL};

		if (cmd == NULL)
			exit(EXIT_FAILURE);

		if (execve(cmd, argv, envp) == -1)
		{
			perror("execve error");
			freeArgv(&argv);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		wait(&status);
	}

	return (0);
}
