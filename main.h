#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define PATH_MAX_LEN 4096
#define MAX_ALIASES 50
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100

typedef struct
{
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
} Alias;

extern char **environ;

void display_prompt(void);
void handle_errors(const char *message);
char* get_user_input(void);
void execute_command(char** args);
void parse_command(char* command, char** args);
int check_command_existence(char *command);
void print_environment(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void change_directory(const char *new_directory);
void handle_commands(char *commands);
int handle_command(char **args);
void print_aliases();
void print_alias(const char *name);
void define_alias(const char *name, const char *value);
char* replace_variables(char* command);
char* replace_str(char* str, const char* find, const char* replace);

#endif /* MAIN_H */