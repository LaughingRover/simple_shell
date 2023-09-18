#include "shell.h"

/**
 * modifyenv - modifies current environment using setenv or unsetenv
 * @argv - argument vector
 *
 * Return: 0 if successful
 */
int modifyenv(char **argv)
{
	char *command = argv[0];
	int result;

	if (_strcmp(command, "setenv") == 0 && (argv[1] != NULL) && (argv[2] != NULL))
	{
		char *name = argv[1];
		char *value = argv[2];

		result = _setenv(name, value, 1);

		return (result);
	}

	if (_strcmp(command, "unsetenv") == 0 && (argv[1] != NULL))
	{
		char *name = argv[1];

		result = _unsetenv(name);

		return (result);
	}

	perror("Error: Environment not modified");
	return (-1);

}
/**
 * _setenv_new - adds a new environment variable
 * @name: name of variable
 * @value: value of variable
 *
 * Return: 0 if successful
 */
int _setenv_new(char *name, char *value)
{
	extern char **environ;
	char **new_environ;
	char **new_env_ptr, **env_ptr;
	size_t new_variable_len = _strlen(name) + _strlen(value) + 2;
	/* +2 is added for '=' and '\0'*/
	char *new_variable = malloc(new_variable_len);

	if (name == NULL || value == NULL)
	{
		perror("No variable name or value found");
		return (-1);
	}

	if (new_variable == NULL)
	{
		perror("Failed to allocate memory");
		return (-ENOMEM);
	}
	new_variable = cat_string(new_variable, name, value, '=');

	/*find the number of variable in environ*/
	env_ptr = environ;
	while (*env_ptr)
		env_ptr++;

	new_environ = malloc((env_ptr - environ + 2) * sizeof(char *));
	/* "(env_ptr - environ)" calculates the number of variables
	in environment and +2 is for the new variable and NULL*/
	if (new_environ == NULL)
	{
		perror("Failed to allocate memory");
		free(new_variable);
		return (-ENOMEM);
	}
	/*copy existing environ into new environ*/
	new_env_ptr = new_environ;
	env_ptr = environ;
	while (*env_ptr)
		*new_env_ptr++ = *env_ptr++;

	*new_env_ptr++ = new_variable;
	*new_env_ptr = NULL;
	/* replace old envrionment with new environment*/
	environ = new_environ;

	return (0);
}

/**
 * _setenv -  changes or adds an environment variable
 * @name: name of variable
 * @value: value of variable
 * @overwrite: integer to modify environment
 *
 * Return: 0 if successful
 */
int _setenv(char *name, char *value, int overwrite)
{
	extern char **environ;
	char *new_variable;
	size_t name_len = _strlen(name);
	size_t new_variable_len = name_len + _strlen(value) + 2;
	/* +2 is added for '=' and '\0'*/

	char **env_ptr = environ;

	while (*env_ptr)
	{
		/* check if existing variable match name*/
		if (_strncmp(*env_ptr, name, name_len) == 0 && ((*env_ptr)[name_len] == '='))
		{
			if (overwrite)
			{
				new_variable = malloc(new_variable_len);
				if (new_variable == NULL)
				{
					perror("Failed to allocate memory");
					return (-1);
				}
				new_variable = cat_string(new_variable, name, value, '=');
				/*replace old variable with new variable*/
				free(*env_ptr);
				*env_ptr = new_variable;

				free(new_variable);
				printf("overwrite suucesful\n");
				return (0);
			}
			else
				return (0); /*variable exist and overwrite is not allowed*/
		}
		env_ptr++;
	}
	/*if the variable does not exist*/
	return (_setenv_new(name, value));
}

/**
 * _unsetenv - removes an environment variable
 * @name: name of variable
 *
 * Return: 0 if successful
 */
int _unsetenv(char *name)
{
	extern char **environ;
	char **env_ptr;
	char **next_env_ptr;
	size_t name_len = _strlen(name);

	if (name == NULL)
	{
		perror("Invalid argument");
		return (-1);
	}
	env_ptr = environ;
	while (*env_ptr)
	{
		/* find environment variable to remove*/
		if (_strncmp(*env_ptr, name, name_len) == 0 && ((*env_ptr)[name_len] == '='))
		{
			free(*env_ptr);

			/*move the remaining variables up the array*/
			next_env_ptr = env_ptr + 1;

			while (*next_env_ptr)
				*env_ptr++ = *next_env_ptr++;

			*env_ptr = NULL;

			return (0);
		}
		env_ptr++;
	}

	return (0); /*variable not found*/
}

