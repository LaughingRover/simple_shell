#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t process_pid;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	process_pid = getpid();
	printf("My pid is %u\n", process_pid);

	if (pid == 0)
	{
		printf("(%u) Nooooooooo!\n", process_pid);
	}
	else
	{
		printf("(%u) %u, I am your father\n", process_pid, pid);
	}

	return (0);
}

