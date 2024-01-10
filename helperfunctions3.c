#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int last_command_exit_status = 0;

/**
 * replace str - Replace all occurrences of a substring in a string
 * @str: The original string
 * @find: The substring to find and replace
 * @replace: The replacement substring
 *
 * Return: A new string with all occurrences of @find replaced by @replace
 */
char *replace_str(char *str, const char *find, const char *replace)
{
    char *result;
    char *ins;
    char *tmp;
    size_t len_find;

    len_find = strlen(find);
    ins = str;

    size_t count = 0;
    while ((tmp = strstr(ins, find)) != NULL)
    {
        ins = tmp + len_find;
        count++;
    }

    result = (char *)malloc(strlen(str) + (strlen(replace) - len_find) * count + 1);

    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    *result = '\0';

    ins = str;
    while (count--)
    {
        tmp = strstr(ins, find);
        size_t len = tmp - ins;
        strncat(result, ins, len);
        strcat(result, replace);
        ins = tmp + len_find;
    }
    strcat(result, ins);
    return (result);
}

/**
 * replace_variables - Replace special variables in the command string
 * @command: The command string
 *
 * Return: A new string with special variables replaced
 */
char *replace_variables(char *command)
{
    char *result = strdup(command);
    char *pos = strstr(result, "$?");
    if (pos != NULL)
    {
        char status_str[10];
        snprintf(status_str, sizeof(status_str), "%d", last_command_exit_status);
        free(result);
        result = replace_str(command, "$?", status_str);
    }

    pos = strstr(result, "$$");
    if (pos != NULL)
    {
        char pid_str[10];
        snprintf(pid_str, sizeof(pid_str), "%d", getpid());
        free(result);
        result = replace_str(command, "$$", pid_str);
    }

    return result;
}

/**
 * handle_commands - Handle multiple commands separated by logical operators
 * @commands: The input commands string
 */
void handle_commands(char *commands)
{
    char *token = commands;
    while (*commands != '\0')
    {
        if (*commands == ';')
        {
            *commands = "\0";
            token = commands + 1;
        }
        commands++;
    }

    while (token != NULL)
    {
        if (token[0] == '#')
            break;
        if (token[strlen(token) - 1] == '\n')
            token[strlen(token) - 1] = '\0';

        char *processed_token = replace_variables(token);
        char *args[MAX_ARGS];
        parse_command(processed_token, args);
        int status = handle_command(args);
        free(processed_token);

        char *logical_op = strstr(token, "&&");
        if (logical_op != NULL)
        {
            if (last_command_exit_status != 0)
                break;
        }
        else
        {
            logical_op = strstr(token, "||");
            if (logical_op != NULL && last_command_exit_status == 0)
                break;
        }
        token = commands;
    }
}

/**
 * handle_command - Handle individual commands and execute built-in commands
 * @args: Array of command arguments
 *
 * Return: The exit status of the command
 */
int handle_command(char **args)
{
    int status = 0;

    if (strcmp(args[0], "exit") == 0)
    {
        handle_exit(args, &status);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        print_environment();
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
        handle_setenv(args);
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        handle_unsetenv(args);
    }
    else if (strcmp(args[0], "alias") == 0)
    {
        handle_alias(args);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        change_directory(args[1]);
    }
    else
    {
        handle_external_command(args, &status);
    }
    return status;
}

void handle_exit(char **args, int *status)
{
    if (args[1] != NULL)
    {
        *status = atoi(args[1]);
        printf("Exiting the shell with status code: %d\n", *status);
        exit(*status);
    }
    else
    {
        printf("Exiting the shell\n");
        exit(EXIT_SUCCESS);
    }
}
void handle_setenv(char **args)
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

void handle_unsetenv(char **args)
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

void handle_alias(char **args)
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
        handle_alias_definition(args);
    }
}

void handle_external_command(char **args, int *status)
{
    if (!check_command_existence(args[0]))
    {
        printf("Command not found: %s\n", args[0]);
        *status = 1;
    }
    else
    {
        execute_command(args);
        *status = 0;
    }
}

void handle_alias_definition(char **args)
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