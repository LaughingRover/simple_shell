#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork + wait + execve
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	char *pathname = argv[0];
	char *envp[] = {NULL};
	int i = 0;
	int status;

	while (i < 5)
	{
		printf("%d\n", i++);
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork error");
			return (1);
		}

		if (child_pid == 0)
		{
			execve(pathname, argv, envp);

			/**
			 * If execve fails print an error message
			 * and continue child process
			 */
			perror("execve error");
			return (1);
		}
		else
		{
			/*Calling process*/
			printf("child exited\n");
			wait(&status);
		}
	}

	return (0);
}
