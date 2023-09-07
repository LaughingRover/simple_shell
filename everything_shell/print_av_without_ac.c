#include <stdio.h>

/**
 * main - prints all the arguments, without using ac
 * @ac: argument count
 * @av: argument variables
 * Return: 0 success, 1 failure
 */
int main(int ac __attribute__((unused)), char **av)
{
	int i = 0;

	while (av[i] != NULL)
	{
		printf("%s ", av[i++]);
	}
	putchar('\n');

	return (0);
}

