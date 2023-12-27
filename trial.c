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

void execute_command(char* command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        handle_errors("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        char** args = (char**)malloc(2 * sizeof(char*));

        if (args == NULL)
        {
            handle_errors("malloc error");
            exit(1);
        }

        args[0] = command;
        args[1] = NULL;

        if (execve(args[0], args, NULL) == -1)
        {
            perror("execve error");
            exit(1);
        }
        free(args);
    }
    else
    {
        wait(NULL);
    }
}