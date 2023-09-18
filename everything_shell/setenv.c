#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _setenv_new - adds a new environment variable
 * @name: name of variable
 * @value: value of variable
 *
 * Return: 0 if successful
 */
int _setenv_new(const char *name, const char *value)
{
	extern char **environ;
	char **new_environ;
	char **new_env_ptr, **env_ptr;
	size_t new_variable_len = strlen(name) + strlen(value) + 2;
	/* +2 is added for '=' and '\0'*/
	char *new_variable = malloc(new_variable_len);

	if (new_variable == NULL)
	{
		perror("Failed to allocate memory");
		return (-1);
	}
	snprintf(new_variable, new_variable_len, "%s=%s", name, value);

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
		return (-1);
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
int _setenv(const char *name, const char *value, int overwrite)
{
	extern char **environ;
	char *new_variable;
	size_t name_len = strlen(name);
	size_t new_variable_len = name_len + strlen(value) + 2;
	/* +2 is added for '=' and '\0'*/

	char **env_ptr = environ;

	while (*env_ptr)
	{
		/* check if existing variable match name*/
		if (strncmp(*env_ptr, name, name_len) == 0 && ((*env_ptr)[name_len] == '='))
		{
			if (overwrite)
			{
				new_variable = malloc(new_variable_len);
				if (new_variable == NULL)
				{
					perror("Failed to allocate memory");
					return (-1);
				}
				snprintf(new_variable, new_variable_len, "%s=%s", name, value);
				/*replace old variable with new variable*/
				free(*env_ptr);
				*env_ptr = new_variable;

				free(new_variable);
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
int _unsetenv(const char *name)
{
	extern char **environ;
	char **env_ptr;
	char **next_env_ptr;
	size_t name_len = strlen(name);

	if (name == NULL)
	{
		perror("Invalid argument");
		return (-1);
	}
	env_ptr = environ;
	while (*env_ptr)
	{
		/* find environment variable to remove*/
		if (strncmp(*env_ptr, name, name_len) == 0 && ((*env_ptr)[name_len] == '='))
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

int main(void)
{
	char *my_var;
	if (_setenv("MY_VARIABLE", "hello world", 1) == 0)
	{
		printf("variable successfully added\n");
	}
	else
		printf("variable unsuccessful\n");
	my_var = getenv("MY_VARIABLE");

	if (my_var != NULL)
		printf("value of my_var = %s\n", my_var);
	else
		printf("my_var not found\n");

	if (_unsetenv("MY_VARIABLE") == 0)
		printf("MY_VARIABLE unset successfully\n");
	else
		printf("failed to unset MY_VARIABLE");

	return (0);
}
