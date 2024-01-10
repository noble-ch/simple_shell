#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
    printf("#cisfun$ ");
}

/**
 * handle_errors - Handles errors and prints an error message
 * @message: The error message to be displayed
 */
void handle_errors(const char *message)
{
    perror(message);
}

/**
 * get_user_input - Reads user input from stdin
 *
 * Return: A pointer to the user input string, or NULL on failure
 */
char *get_user_input(void)
{
    char *input = NULL;
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

/**
 * parse_command - Parses the command string into separate arguments
 * @command: The command string to be parsed
 * @args: An array to store the parsed arguments
 */
void parse_command(char *command, char **args)
{
    char *token;
    int index;

    token = command;
    index = 0;

    while (*token != '\0')
    {
        if (*token == " ")
        {
            *token = '\0';
            args[index++] = command;
            command = token + 1;
        }
        token++;
    }
    args[index++] = command;
    args[index] = NULL;

    if (index >= MAX_ARGS)
    {
        fprintf(stderr, "Too many arguments. Increase MAX_ARGS.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * execute_command - Executes a command with its arguments
 * @args: An array containing the command and its arguments
 */
void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        handle_errors("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "Cmd not found: %s\n", args[0]);
            exit(1);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}