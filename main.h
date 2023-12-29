#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define PATH_MAX_LEN 4096

extern char **environ;

void display_prompt(void);
void handle_errors(const char *message);
char* get_user_input(void);
void execute_command(char** args);
void parse_command(char* command, char** args);
int check_command_existence(char *command);
void print_environment(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif /* MAIN_H */