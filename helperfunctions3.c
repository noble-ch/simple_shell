#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



/**
 * replace str - Replace all occurrences of a substring in a string
 * @str: The original string
 * @find: substring to finding and replace
 * @replace: The replacement substring
 *
 * Return: A new string with all occurrences of @find replaced by @replace
 */

size_t count = 0;
size_t len_find;
size_t len;
int last_command_exit_status = 0;

char *replace_str(char *str, const char *find, const char *replace)
{
char *result;
char *ins;
char *tmp;
len_find = strlen(find);
ins = str;

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
len = tmp - ins;
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
 * handle_commands - Handles multiple commands separated by logical operators like || &&
 *
 * @commands: The input commands string
 */
void handle_commands(char *commands)
{
char *pos = commands;
int status;
char *args[MAX_ARGS];
char op;
char *logical_op_and;
char *logical_op_or;
char *next_token;
char *processed_token;
char *token;
int continue_exec;
while (*pos != '\0')
	{
	char *end = strchr(pos, ';');
	if (end != NULL)
	{
	*end = '\0';
	}

	if (*pos == '#')
	{
	break;
	}
	processed_token = replace_variables(pos);
	token = processed_token;
	continue_exec = 1;
	while (continue_exec && *token != '\0')
	{
	logical_op_and = strstr(token, "&&");
	logical_op_or = strstr(token, "||");
	next_token = NULL;
		if (logical_op_and != NULL && (logical_op_or == NULL || logical_op_and < logical_op_or))
		{
		next_token = logical_op_and;
		}
		else if (logical_op_or != NULL && (logical_op_and == NULL || logical_op_or < logical_op_and))
		{
		next_token = logical_op_or;
		}
		else
		{
		next_token = token + strlen(token);
		}
		op = '\0';
		if (next_token != NULL)
		{
		op = *next_token;
		*next_token = '\0';
		}
		parse_command(token, args);
		status = handle_command(args);
		if ((op == '&' && status != 0) || (op == '|' && status == 0))
		{
		continue_exec = 0;
		}

		if (next_token != NULL)
		{
		*next_token = op;
		token = next_token + 2;
		}
		else
		{
		break;
		}
		}
		if (end != NULL)
        {
            *end = ';';
            pos = end + 1;
        }
        else
        {
            break;
        }

        free(processed_token);
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
        if (args[1] != NULL)
        {
            status = atoi(args[1]);
            printf("Exiting the shell with status code: %d\n", status);
            exit(status);
        }
        else
        {
            printf("Exiting the shell\n");
            exit(EXIT_SUCCESS);
        }
    }
    else if (strcmp(args[0], "env") == 0)
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
    else if (strcmp(args[0], "cd") == 0)
    {
        change_directory(args[1]);
    }
    else
    {
        if (!check_command_existence(args[0]))
        {
            printf("Command not found: %s\n", args[0]);
            status = 1;
        }
        execute_command(args);
    }
    return status;
}

/**
 * handle_variables - Replace special variables in the command string
 * @command: The command string
 *
 * Return: A new string with special variables replaced
 */
char *handle_variables(char *command)
{
    char *result = strdup(command);
    char *pos = result;
    int escaped = 0;

    while (*pos != '\0')
    {
        if (*pos == '\\' && !escaped)
        {
            escaped = 1;
            pos++;
            continue;
        }

        if (*pos == '$' && *(pos + 1) == '$' && !escaped)
        {
            char pid_str[10];
            snprintf(pid_str, sizeof(pid_str), "%d", getpid());
            result = replace_str(result, "$$", pid_str);
            pos += 2;
        }
        else if (*pos == '$' && *(pos + 1) == '?' && !escaped)
        {
            char status_str[10];
            snprintf(status_str, sizeof(status_str), "%d", last_command_exit_status);
            result = replace_str(result, "$?", status_str);
            pos += 2;
        }
        else
        {
            pos++;
        }

        escaped = 0;
    }

    return result;
}
