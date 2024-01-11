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
void handle_exit(char **args, int *status);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_alias(char **args);
void handle_external_command(char **args, int *status);
void handle_alias_definition(char **args);
void process_token(char *token, int *last_command_exit_status);
void check_logical_ops(char *logical_op, int *last_command_exit_status);

#endif /* MAIN_H */
