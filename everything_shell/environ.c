#include <stdio.h>
#include <unistd.h>

/**
 * main - prints environment variable using global variable environ
 *
 * Return: 0 success.
 */
int main()
{
	unsigned int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}
