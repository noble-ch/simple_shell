#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 50
#define PATH_MAX_LEN 4096
#define MAX_ALIASES 50
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100
#define INITIAL_BUFFER_SIZE 128

/**
 * Structure to represent an alias with a name and value
 */
typedef struct
{
    char name[MAX_ALIAS_NAME];   /** The name of the alias */
    char value[MAX_ALIAS_VALUE]; /** The value of the alias */
} Alias;

/**
 * External environment variable.
 */
extern char **environ;

void display_prompt(void);
void handle_errors(const char *message);
char *get_user_input(void);
void execute_command(char **args);
void parse_command(char *command, char **args);
int check_command_existence(char *command);
void print_environment(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void change_directory(const char *new_directory);
void handle_commands(char *commands);
int handle_command(char **args);
void print_aliases();
void print_alias(const char *name);
void define_alias(const char *name, const char *value);
char *replace_variables(char *command);
char *replace_str(char *str, const char *find, const char *replace);

#endif /* MAIN_H */