#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

void prompt(void);
int executeCommand(char **argv);

int getArgv(char *input_line, char ***argv);
void freeArgv(char ***argv);
int resizeArgv(char ***argv, size_t *max_argc);

void trim(char **str);

size_t _strlen(const char *str);
char *_strchr(const char *str, int character);
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);


#endif /*SHELL_H*/
