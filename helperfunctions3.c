#include "main.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * getline_function - print "$ " and wait for input.
 * Return: user input
 */

char *getline_function(void)
{
	char *lineptr = NULL;
	size_t charter_user = 0;

	if (isatty(STDIN_FILENO))
		display_prompt();

	if (getline(&lineptr, &charter_user, stdin) == -1)
	{
		free(lineptr);
		return (NULL);
	}

	return (lineptr);
}

/**
 * path_var - gets the variable of the PATH.
 * @env: local enviroment
 * Return: PATH value.
 */

char *path_var(char **env)
{
	size_t i = 0, var = 0, count = 5;
	char *path = NULL;

	while (comp_string(env[i], "PATH=", 5))
	{
		i++;
	}

	if (env[i] == NULL)
	{
		return NULL;
	}

	count = 5;

	while (env[i][var])
	{
		var++;
		count++;
	}
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	var = 5;
	count = 0;

	while (env[i][var])
	{
		path[count] = env[i][var];
		var++;
		count++;
	}

	path[count] = '\0';
	return (path);
}
