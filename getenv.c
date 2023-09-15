#include "shell.h"

/**
 * _getenv - gets an environment variable.
 * @name: variable name.
 *
 * Return: returns pointer to value in environment or NUll if not found.
 */
char *_getenv(const char *name)
{
	extern char **environ;
	char **environ_copy;
	char *current_var;
	unsigned int length = _strlen(name);


	environ_copy = environ;
	while (*environ_copy != NULL)
	{
		current_var = *environ_copy;

		/*checks if the current VAR matches name*/
		if ((_strncmp(current_var, name, length) == 0) &&
				(current_var[length] == '='))
		{
			return (current_var + length + 1);
			/*+1 is added to skip the '=' char*/
		}

		environ_copy++;
	}

	return (NULL);
}

