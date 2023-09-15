#include "shell.h"

/**
 * _strncmp - Function that compare two strings up to specific length
 * @str1: first string
 * @str2: second string
 * @n: amount of bytes to compare
 *
 * Return: 0 if second string is found in first string.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if ((*str1 == '\0') || (*str2 == '\0'))
			break;
		str1++;
		str2++;
		n--;
	}

	return (0);
}

/**
 * _strcmp - Function that compare two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 if second string is found in first string.
 */
int _strcmp(const char *str1, const char *str2)
{
	while ((*str1++ & *str2++))
	{
		if (*str1 != *str2)
			return (-1);
	}

	return (0);
}

/**
 * construct_full_path - concatenate two strings with the delimiter "/"
 * @dest: destination of the concatenated string
 * @str1: first string
 * @str2: second string
 *
 * Return: return concatenated string
 */
char *construct_full_path(char *dest, char *str1, char *str2)
{
	size_t str1_len = _strlen(str1);
	const char delim = '/';
	size_t dest_len = 0;

	_strcpy(dest, str1);

	/*check if the delimiter can be added*/
	if (str1_len > 0)
	{
		dest[str1_len] = delim;
		dest[str1_len + 1] = '\0';
	}
	/*get the length of resulting string*/
	dest_len = _strlen(dest);

	_strcpy(dest + dest_len, str2);

	return (dest);
}

/**
 *  printenv - prints environment variable
 */
void printenv(void)
{
	unsigned int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
