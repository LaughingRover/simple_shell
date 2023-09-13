#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * path_directory - prints each directory contained in the the environment variable
 * PATH, one directory per line.
 *
 * Return - always 0
 */
int path_directory(void)
{
	char *value = getenv("PATH");
	char *token;

	if (!value)
	{
		printf("Environment variable not found\n");
		return (1);
	}

	token = strtok(value, ":");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

	return (0);
}

/**
 * main - test the code
 *
 * Return: always 0
 */
int main(void)
{
	path_directory();

	return (0);
}

