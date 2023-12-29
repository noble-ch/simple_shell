#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void display_prompt(void)
{
    printf("#cisfun$ ");
}

void handle_errors(const char* message)
{
    perror(message);
}

char* get_user_input(void)
{
    char* input = NULL;
    size_t bufsize = 0;


    if (getline(&input, &bufsize, stdin) == -1)
    {
        handle_errors("getline error");
        return NULL;
    }

    if (input[strlen(input) - 1] == '\n')
    {
        input[strlen(input) - 1] = '\0';
    }

    return (input);
}

void parse_command(char* command, char** args)
{
    char* token;
    int index = 0;

    token = strtok(command, " ");
    args[index++] = token;

    while (token != NULL && index < MAX_ARGS - 1)
    {
        token = strtok(NULL, " ");
        args[index++] = token;
    }
    args[index] = NULL;
}

void execute_command(char** args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        handle_errors("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }
}