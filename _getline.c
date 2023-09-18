#include "shell.h"

#define INITIAL_BUFSIZ 128

ssize_t read_line(char **lineptr, size_t *n, int fd, char *buffer);

/**
 * resize_getline_buf - resize the memory size of the buffer
 * @lineptr: buffer
 * @n: The buffer size allocated to the line
 * @new_size: new size of memory
 *
 * Return: 0 on success, -ENOMEM on failure
*/
int resize_getline_buf(char **lineptr, size_t *n, size_t new_size)
{
	char *newline = _realloc(*lineptr, new_size);

	if (newline == NULL)
	{
		free(*lineptr);
		return (-ENOMEM);
	}
	*lineptr = newline;
	*n = new_size;

	return (0);
}

/**
 * _getline - retrieves a line from stream
 * @lineptr: The line is stored in the memory pointed to by the lineptr
 * @n: The buffer size allocated to the line
 * @stream: The file stream the line is gotten from
 *
 * Return: The amount of bytes read is returned on success,
 * on error or EOF -1 is returned
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[INITIAL_BUFSIZ];
	size_t bufsiz = (*n > 0) ? *n : INITIAL_BUFSIZ;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-EINVAL);
	if (*lineptr == NULL || *n <= 0)
	{
		*n = bufsiz;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-ENOMEM);
	}

	return(read_line(lineptr, n, stream->_fileno, buffer));
}


ssize_t read_line(char **lineptr, size_t *n, int fd, char *buffer UNUSED)
{
	ssize_t total_bytes_read = 0;

	while (1)
	{
		ssize_t bytes_read = read(fd, *lineptr + total_bytes_read, 1);

		if (bytes_read == -1)
		{
			return (-1);
		}

		total_bytes_read += bytes_read;
		if (bytes_read == 0 || (*lineptr)[total_bytes_read - 1] == '\n')
		{
			if (bytes_read == 0 && total_bytes_read == 0)
				return (EOF);

			return (total_bytes_read);
		}

		if (total_bytes_read >= (ssize_t)(*n - 1))
		{
			size_t new_size = *n * 2;
			int result = resize_getline_buf(lineptr, n, new_size);

			if (result)
				return (result);
		}
	}
}
