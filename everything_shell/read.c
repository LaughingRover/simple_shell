#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char line[1024];
	ssize_t total_bytes_read = 0;
	ssize_t bytes_read;

	while (1)
	{
		bytes_read = read(STDIN_FILENO, line + total_bytes_read, 1);

		if (bytes_read < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (bytes_read == 0)
		{
			break;
		}
		else
		{
			total_bytes_read += bytes_read;
			if (line[total_bytes_read - 1] == '\n')
			{
				break;
			}
		}
	}
	line[total_bytes_read] = '\0';
	printf("%s", line);

	return 0;
}
