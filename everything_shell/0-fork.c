#include <stdio.h>
#include <unistd.h>

/**
 *main - fork example
 *
 *Return: Always 0.
 */
int main(void)
{
	pid_t calling_pid;
	pid_t child_pid;
	pid_t parent_pid;
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	if (pid == 0)
	{
		printf("After fork\n");

		child_pid = getpid();
		calling_pid = getppid();

		printf("child pid is %u\n", child_pid);
		printf("process pid is %u\n", calling_pid);
	}
	else
	{
		printf("before fork\n");

		calling_pid = getpid();
		parent_pid = getppid();

		printf("process is %u\n", calling_pid);
		printf("bash pid(parent) is %u\n", parent_pid);
	}

	return (0);
}

