#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * print_aliases - Prints all defined aliases
 */
void print_aliases(void)
{
	int i;
	int alias_count;
	Alias aliases[MAX_ALIASES];

	alias_count = 0;
	for (i = 0; i < alias_count; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * print_alias - Prints the value of a specific alias
 * @name: The name of the alias to be printed
 */
void print_alias(const char *name)
{
	int i;
	int alias_count;
	Alias aliases[MAX_ALIASES];

	alias_count = 0;
	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			printf("%s='%s'\n", aliases[i].name, aliases[i].value);
		}
	}
}

/**
 * define_alias - Defines a new alias or updates an existing one
 * @name: The name of the alias to be defined or updated
 * @value: The value of the alias
 */
void define_alias(const char *name, const char *value)
{
	int existing_alias_index;
	int i;
	int alias_count;
	Alias aliases[MAX_ALIASES];

	existing_alias_index = -1;
	alias_count = 0;
	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			existing_alias_index = i;
			break;
		}
	}
	if (existing_alias_index != -1)
	{
		strcpy(aliases[existing_alias_index].value, value);
	}
	else
	{
		if (alias_count < MAX_ALIASES)
		{
			strcpy(aliases[alias_count].name, name);
			strcpy(aliases[alias_count].value, value);
			alias_count++;
		}
		else
		{
			fprintf(stderr, "Max number of aliases reached\n");
		}
	}
}

/**
 * process_token - Process the given token
 * @token: The token to be processed
 * @last_command_exit_status: Pointer to the exit status of the last command
 */

void process_token(char *token, int *last_command_exit_status)
{
	char *processed_token;
	char *args[MAX_ARGS];
	char *logical_op;

	logical_op = strstr(token, "&&");
	processed_token = replace_variables(token);
	parse_command(processed_token, args);
	*last_command_exit_status = handle_command(args);
	free(processed_token);
	check_logical_ops(logical_op, last_command_exit_status);
}

/**
 * check_logical_ops - Check for logical operators in the token
 * @logical_op: Pointer to the logical operator in the token
 * @last_command_exit_status: Pointer to the exit status of the last command
 */

void check_logical_ops(char *logical_op, int *last_command_exit_status)
{
	char *token = NULL;

	if (logical_op != NULL)
	{
		if (*last_command_exit_status != 0)
			return;
	}
	else
	{
		token = strstr(logical_op, "||");
		if (token != NULL && *last_command_exit_status == 0)
			return;
	}
}
