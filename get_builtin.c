#include "shell.h"

/**
 * handle_builtins - handles builtin function
 * @cmd: command to check if it's a builtin
 *
 * Return: builtin function, NULL if it doesn't exist
 */
int (*handle_builtins(char *cmd))(char ***argv)
{
	builtin_t builtins[] = {
		{"exit", builtin_exit},
		{"printenv", printenv},
		{"env", printenv},
		{"setenv", modifyenv},
		{"unsetenv", modifyenv},
		{"cd", change_working_dir},
	};
	int i = 0;

	while (i < (int)(sizeof(builtins) / sizeof(builtins[i])))
	{
		if (_strcmp(cmd, builtins[i].name) == 0)
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

