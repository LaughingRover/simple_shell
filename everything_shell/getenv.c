#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
	unsigned int length = strlen(name);


	environ_copy = environ;
	while (*environ_copy != NULL)
	{
		current_var = *environ_copy;

		/*checks if the current VAR matches name*/
		if ((strncmp(current_var, name, length) == 0) && (current_var[length] == '='))
		{
			return (current_var + length + 1);
			/*+1 is added to skip the '=' char*/
		}

		environ_copy++;
	}

	return (NULL);
}

/**
 * main - get enviroment variable PATH
 *
 * Return: 0 always success
 */
int main(void)
{
	const char *name = "LANGUAGE";
	char *value = _getenv(name);

	if (value != NULL)
		printf("%s= %s\n", name, value);
	else
		printf("Environment variable %s not found\n", name);

	return (0);
}

