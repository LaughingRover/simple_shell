#include "shell.h"

/**
 * prompt - prints prompt to the output
 */
void prompt(void)
{
	char *prompt = "$ ";
	size_t prompt_len = _strlen(prompt);

	write(STDOUT_FILENO, prompt, prompt_len);
	fflush(stdout); /*Ensure the prompt is displayed immediately*/
}

/**
 * get_argv - splits string gotten from stdin
 * @input_line: string to split
 * @argv: is updated with tokenized string
 * @delim: delimiter
 *
 * Return: number of arguments parsed (argc) or -1 in case of an error
 */
int get_argv(char *input_line, char ***argv, const char *delim)
{
	char *token = NULL;
	size_t max_argc = 16;
	size_t argc = 0;

	*argv = malloc(sizeof(char *) * max_argc);
	if (*argv == NULL)
	{
		perror("Memory allocation failed");
		return (-1);
	}

	token = _strtok(input_line, delim);
	while (token != NULL)
	{
		trim(&token);

		(*argv)[argc] = _strdup(token);
		if ((*argv)[argc] == NULL)
		{
			perror("Memory allocation failed");
			free_argv(argv);
			return (-1);
		}

		token = _strtok(NULL, delim);
		argc++;

		if (argc >= max_argc)
		{
			if (resize_argv(argv, &max_argc) != 0)
				return (-1);
		}
	}

	return (argc);
}

/**
 * free_argv - frees an array of strings
 * @argv: pointer to an array of strings
 */
void free_argv(char ***argv)
{
	size_t i = 0;

	while ((*argv)[i] != NULL)
	{
		free((*argv)[i]);
		i++;
	}
	free(*argv);
}

/**
 * resize_argv - Resizes the argv array by doubling its size
 * @argv: pointer to an array of strings
 * @max_argc: size of argv
 *
 * Return: 0 success, 1 failure
 */
int resize_argv(char ***argv, size_t *max_argc)
{
	char **new_argv;
	size_t new_size, i;
	*max_argc *= 2;

	new_size = *max_argc * sizeof(char *);
	new_argv = _realloc(*argv, new_size);
	if (new_argv == NULL)
		return (-ENOMEM);

	/*Copy existing pointers to the new array*/
	for (i = 0; i < *max_argc / 2; i++)
	{
		new_argv[i] = (*argv)[i];
	}

	free_argv(argv); /*Free the old array*/
	*argv = new_argv;

	return (0);
}

/**
 * trim - Trim leading and trailing whitespace from a string
 * @str: string
 */
void trim(char **str)
{
	char *start = *str;
	char *end = *str + _strlen(*str) - 1;

	/*Find the index of the first non-whitespace character*/
	while (*start && (*start == ' ' || *start == '\t'))
	{
		start++;
	}

	/*Find the index of the last non-whitespace character*/
	while (end > start && (*end == ' ' || *end == '\t'))
	{
		end--;
	}

	/*Null-terminate the trimmed string*/
	end[1] = '\0';

	/*Update the pointer to the trimmed string*/
	*str = start;
}
