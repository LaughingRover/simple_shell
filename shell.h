#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

void prompt(void);
int executeCommand(char **argv);
char *handlePath(char *cmd);

int getArgv(char *input_line, char ***argv);
void freeArgv(char ***argv);
int resizeArgv(char ***argv, size_t *max_argc);
char *_getenv(const char *name);
void printenv(void);

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
