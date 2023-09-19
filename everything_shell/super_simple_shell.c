#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * execute_command - executes a command with full path
 * @command: full path
 *
 * Return: 0 on success, 1 on failure
 */
void execute_command(const char *command)
{
	pid_t child_pid;
	int status;
	char *argv[] = {"command", NULL};

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* This code runs in the child process*/
		if (execve(command, argv, NULL) == -1)
		{
			perror("exec error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*This runs in the parent process*/
		wait(&status);
	}
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_len;

	while (1)
	{
		printf("SS-Shell> ");
		fflush(stdout);

		read_len = getline(&line, &len, stdin);
		if (read_len == -1)
		{
			perror("getline error");
			exit(EXIT_FAILURE);
		}

		/*Remove the newline character if present*/
		if (line[read_len - 1] == '\n')
		{
			line[read_len - 1] = '\0';
		}

		execute_command(line);
	}

	return (0);
}
