#include "shell.h"

/**
 * executeCommand - executes a command with arguments
 * @argv: array of command and arguments
 *
 * Return: 0 on success, 1 on failure
 */
int executeCommand(char **argv)
{
	char *cmd_path = argv[0];
	pid_t child_pid;

	if (access(cmd_path, X_OK) != 0)
		cmd_path = handlePath(cmd_path);

	if (cmd_path == NULL)
	{
		perror("Command not found");
		return (-1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		return (-1);
	}

	if (child_pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(cmd_path, argv, envp) == -1)
		{
			perror("execve error");
		}
	}
	else
	{
		int status;

		wait(&status);
	}

	return (0);
}

/**
 * handlePath - returns fullpath of command passed
 * @cmd: command passed
 *
 * Return: return fullpath of command passed
 */
char *handlePath(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_copy;
	char *token;
	char *full_path = malloc(sizeof(char) * 1024);

	path_copy = _strdup(path);
	if ((path == NULL) || (path_copy == NULL))
	{
		perror("PATH not found");
		return (NULL);
	}

	token = _strtok(path_copy, ":");
	while (token)
	{
		/*concatenate the token in PATH with the command passed*/
		full_path = construct_full_path(full_path, token, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
