#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * handle_setenv - Handle the setenv command and set environment variables
 * @args: Array of command arguments
 *
 * Description: This function handles the setenv command and sets the
 * environment variables based on provided arguments. If the correct number
 * of arguments is provided, it sets the environment variable. Otherwise,
 * it displays an error message.
 */

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

/**
 * handle_unsetenv - Handle the unsetenv command and unset environment
 * variables.
 * @args: Array of command arguments
 *
 * Description: This function handles the unsetenv command and unsets
 * environment variables based on provided arguments. If the correct
 * argument is provided, it unsets the environment variable. Otherwise,
 * it displays an error message.
 */

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

/**
 * handle_alias - Handle the alias command and perform alias operations
 * @args: Array of command arguments
 *
 * Description: This function handles the alias command and performs alias
 * operations based on the provided arguments. If no arguments are provided,
 * it prints all aliases. If one argument is provided, it prints the alias
 * definition. If more than one argument is provided, it handles alias
 * definition.
 */

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

/**
 * handle_external_command - Handles external commands and executes them.
 * @args: Array of command arguments
 * @status: Pointer to exit status
 *
 * Description: This function handles external commands and executes them using
 * the provided arguments. It checks for the existence of the
 * command and executes it.
 */

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

/**
 * handle_alias_definition - Handle alias definition and define aliases
 * @args: Array of command line arguments
 *
 * Description: This function handles alias definition and defines aliases
 * based on provided arguments. It parses the arguments and defines aliases
 * accordingly. It displays an error message for invalid alias definitions.
 */

void handle_alias_definition(char **args)
{
	int arg_index;
	char *equal_sign;

	arg_index = 1;
	while (args[arg_index] != NULL)
	{
		equal_sign = strchr(args[arg_index], '=');
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
