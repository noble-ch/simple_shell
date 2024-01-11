#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * *replace_str - Replace all occurrences of a substring in a string
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
	size_t count;
	size_t len;

	len_find = strlen(find);
	ins = str;
	count = 0;
	while ((tmp = strstr(ins, find)) != NULL)
	{
		ins = tmp + len_find;
		count++;
	}
	result = (char *)malloc(strlen(str) + (strlen(replace) - len_find)
			* count + 1);
	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	result = '\0';
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
	char *result;
	char *pos;
	int last_command_exit_status;

	last_command_exit_status = 0;
	result = strdup(command);
	pos = strstr(result, "$?");
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
	return (result);
}

/**
 * handle_commands - Handle multiple commands separated by logical operators
 * @commands: The input commands string
 *
 * Return: void
 */
void handle_commands(char *commands)
{
	char *token;
	/* char *logical_op; */
	/* int status; */
	int last_command_exit_status;

	last_command_exit_status = 0;
	token = commands;
	while (*commands != '\0')
	{
		if (*commands == ';')
		{
			*commands = '\0';
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
		process_token(token, &last_command_exit_status);
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
	int status;

	status = 0;
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
	return (status);
}

/**
 * handle_exit - Handle the exit command and exit the shell
 * @args: Array of command arguments
 * @status: Pointer to the exit status
 *
 * Description: This function handles the exit command and exits the
 * shell with the specified status. If a status is provided as an argument
 * the shell exits with that status. If no status is provided, the shell
 * exits with EXIT_SUCCESS.
 */

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
