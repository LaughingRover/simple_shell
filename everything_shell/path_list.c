#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct PATH - PATH directories
 * @directory: PATH directory
 * @next: link to next node in list.
 *
 * Description: structure oflinked list to enviroment "PATH" directories
 */
typedef struct PATH
{
	char *directory;
	struct PATH *next;
} PATH;

/**
 * build_path_list -  builds a linked list of the PATH directories.
 *
 * Return: returns the pointer to head of a linked list
 */
PATH *build_path_list(void)
{
	PATH *head = NULL, *current_directory = NULL;
	char *token;
	char *value = getenv("PATH");
	PATH *new_directory;

	token = strtok(value, ":");
	while (token)
	{
		new_directory = malloc(sizeof(PATH));
		if (!new_directory)
			return (NULL);

		new_directory->directory = strdup(token);
		new_directory->next = NULL;

		if (!head)
		{
			head = new_directory;
			current_directory = new_directory;
		}
		else
		{
			current_directory->next = new_directory;
			current_directory = new_directory;
		}

		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * main - test the code
 *
 * Return: always 0
 */
int main(void)
{
	PATH *path_list, *current;

	path_list = build_path_list();
	current = path_list;

	while (current)
	{
		printf("%s\n", current->directory);
		current = current->next;
	}
	/*free path_list*/
	while (path_list)
	{
		PATH *temp = path_list;
		path_list = path_list->next;

		free(temp->directory);
		free(temp);
	}

	return (0);
}

