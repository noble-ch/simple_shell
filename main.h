#ifndef MAIN_H
#define MAIN_H
#define _GNU_SOURCE
#define BUFFER_SIZE 1024


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;


int comp_strval(char *str1, char *str2);
size_t comp_string(char *str1, char *str2, size_t n);
int string_len(char *s);
char *string_copy(char *destination, char *source);
char *concat(char *destnation, char *source);
int _putchar(char c);
char *custom_getline();
char *path_var(char **env);
int values_path(char **arg, char **env);
char *getline_function(void);
void get_enviroment(char **env);
char **get_token(char *line_pointer);
void built_in_exit(char **args, char *line_pointer, int terminate);
int fork_f(char **arg, char **PID, char **env,
			  char *lineptr, int n, int c);
char *strtokenize(char *str, const char *delim);

#endif /* MAIN_H */
