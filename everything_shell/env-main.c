#include <stdio.h>
#include <stdlib.h>

/**
 * prints the environment and addresses of env and environ
 *
 * Return: Always 0 success
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;
	extern char **environ;
	(void)ac;
	(void)av;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}

	printf("address of env: %p\n", env);
	printf("address of environ: %p\n", environ);
	return (0);
}

