#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#endif

extern char **environ;

/**
 * struct builtin_t - builtin function
 * @name: name of builtin function
 * @func: pointer to builtin function
*/
typedef struct builtin_t
{
	char *name;
	int (*func)(char ***argv);

} builtin_t;

void prompt(void);
int commandline_mode(int *argc, char ***argv, char ***env);
void interactive_mode(int *argc, char ***argv, char ***env);
char *handle_path(char *cmd);
char *construct_full_path(char *dest, char *str1, char *str2);
int execute_command(char **argv);

/*-----------builtin function------------------*/
int (*handle_builtins(char *s))(char ***argv);
typedef int (*get_builtin)(char ***argv);
int modifyenv(char ***argv);
int builtin_exit(char ***argv);
int printenv(char ***argv UNUSED);
int change_working_dir(char ***argv);
/*--------------------------------------------*/

void trim(char **str);
int get_argv(char *input_line, char ***argv);
void free_argv(char ***argv);
int resize_argv(char ***argv, size_t *max_argc);
char *_getenv(const char *name);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t readline(char **lineptr, size_t *n, int fd);
int resize_getline_buf(char **lineptr, size_t *n, size_t new_size);
int set_new_env(char *name, char *value);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

size_t _strlen(const char *str);
char *_strchr(const char *str, int character);
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
char *cat_string(char *dest, char *str1, char *str2, char delim);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strcmp(const char *str1, const char *str2);

char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, size_t size);

#endif /*SHELL_H*/
