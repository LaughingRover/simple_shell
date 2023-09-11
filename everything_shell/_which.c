#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/**
 * main - Entry point of the program
 *
 * Return: 0 success, 1 if fail
 */
int main(int argc, char *argv[])
{
	const char *filename = argv[1];
	const char *path = getenv("PATH");
	char *path_copy, *token;
	char full_path[1024];

	if ((argc != 2) || (path == NULL))
	{
		perror("Error:");
		return (1);
	}

	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("Error:");
		return (1);
	}

	token = strtok(path_copy, ":");
	while (token)
	{
		/* concatenate the token found in PATH with the file passed*/
		snprintf(full_path, sizeof(full_path), "%s/%s", token, filename);

		if (access(full_path, F_OK) == 0)
		{
			printf("%s\n", full_path);
			free(path_copy);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (1);
}

