#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void handle_commands(char *commands)
{
    char *token = strtok(commands, ";");
    while (token != NULL)
    {
        if (token[strlen(token) - 1] == '\n')
            token[strlen(token) - 1] == '\0';

        char *args[MAX_ARGS];
        parse_command(token, args);
        handle_command(args);
        token = strtok(NULL, ";");
    }
}

void handle_command(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        if (args[1] != NULL)
        {
            int status = atoi(args[1]);
            printf("Exiting the shell with status code: %d\n", status);
            exit(status);
        }
        else
        {
            printf("Exiting the shell\n");
            exit(EXIT_SUCCESS);
        }
    }
    else if(strcmp(args[0], "env") == 0)
    {
        print_environment();
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
        if (args[1] != NULL && args[2] != NULL)
        {
            if (setenv(args[1], args[2], 1) != 0)
                fprintf(stderr, "Failed to set env variable\n");
        }
        else
        {
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        }
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        if (args[1] != NULL)
        {
            if (unsetenv(args[1]) != 0)
                fprintf(stderr, "Failed to unset env variable\n");
        }
        else
        {
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        }
    }
    else if (strcmp(args[0], "alias") == 0)
    {
        if (args[1] == NULL)
        {
            print_aliases();
        }
        else if (args[2] == NULL)
        {
            print_alias(args[1]);
        }
        else
        {
            int arg_index = 1;
            while (args[arg_index] != NULL)
            {
                char *equal_sign = strchr(args[arg_index], '=');
                if (equal_sign != NULL)
                {
                    *equal_sign = '\0';
                    define_alias(args[arg_index], equal_sign + 1);
                }
                else
                {
                    fprintf(stderr, "Invalid alias definition: %s\n", args[arg_index]);
                }
                arg_index++;
            }
        }
    }
    else if(strcmp(args[0], "cd") == 0)
    {
        change_directory(args[1]);
    }
    else
    {
        if (!check_command_existence(args[0]))
        {
            printf("Command not found: %s\n", args[0]);
        }
        execute_command(args);
    }
}