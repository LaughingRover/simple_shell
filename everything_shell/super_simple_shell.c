#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1024

void stripNewline(char *str)
{
	size_t len = strlen(str);

	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0'; /*Replace '\n' with null-terminator*/
	}
}

int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("Shell> ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break; /*Exit on EOF (e.g., Ctrl+D)*/
		}

		stripNewline(input);

		/*Parse the command and path*/
		char *command = strtok(input, " ");
		char *path = strtok(NULL, " ");

		if (command == NULL)
		{
			printf("No command provided.\n");
			continue; /*Continue if no command is provided*/
		}

		/*Resolve the absolute path of the command*/
		char absolutePath[PATH_MAX];

		if (realpath(command, absolutePath) == NULL)
		{
			perror("realpath");
			continue; /*Continue if command not found*/
		}

		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			/*Child process*/
			if (execl(absolutePath, absolutePath, (char *)NULL) == -1)
			{
				perror("exec error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/*Parent process*/
			int status;

			wait(&status);
		}
	}

	return (0);
}
