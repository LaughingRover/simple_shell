#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prompt();
char **split_string(char *str, const char *delim);
void free_str_array(char **str_ptr);

/**
 * main - Entry point
 * Return: 0 success, 1 failure
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv = NULL;

	prompt();
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		/*Print the entered command*/
		printf("%s", line);

		argv = split_string(line, " ");

		/*Print the next prompt*/
		prompt();
	}
	free(line);
	free_str_array(argv);
	return (0);
}

void prompt()
{
	printf("$ ");
	fflush(stdout);  /*Ensure the prompt is displayed immediately*/
}

/**
 * split_string - splits a string by the space delimiter
 * @str: string to split
 * @delim: character to split by e.g. ',' ':' ';'
 *
 * Return: an array of each word of the string
 */
char **split_string(char *str, const char *delim)
{
	char *token = NULL;
	char **array_token = malloc(sizeof(char *) * 1024);
	size_t i = 0, j = 0;

	token = strtok(str, delim);
	while (token != NULL)
	{
		array_token[i] = strdup(token);

		if (array_token[i] == NULL)
		{
			for (j = 0; j <= i; j++)
			{
				free(array_token[j]);
			}
			free(array_token);
			return (NULL);
		}


		token = strtok(NULL, delim);
		i++;
	}

	return (array_token);
}

/**
 * free_str_array - frees an array of strings
 * @str_ptr: pointer to strings
 */
void free_str_array(char **str_ptr)
{
	size_t i = 0;

	while (str_ptr[i] != NULL)
	{
		free(str_ptr[i]);
		i++;
	}
	free(str_ptr);
}

