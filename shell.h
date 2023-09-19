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

void prompt(void);
int executeCommand(char **argv);
char *handlePath(char *cmd);
int commandline_mode(int *argc, char ***argv, char ***env);
void interactive_mode(int *argc, char ***argv, char ***env);
void change_working_dir(char **argv);

int getArgv(char *input_line, char ***argv);
void freeArgv(char ***argv);
int resizeArgv(char ***argv, size_t *max_argc);
char *_getenv(const char *name);
void *_realloc(void *ptr, size_t size);
void printenv(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t read_line(char **lineptr, size_t *n, int fd);
int resize_getline_buf(char **lineptr, size_t *n, size_t new_size);

void trim(char **str);

size_t _strlen(const char *str);
char *_strchr(const char *str, int character);
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
char *construct_full_path(char *dest, char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strcmp(const char *str1, const char *str2);

#endif /*SHELL_H*/
