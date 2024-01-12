#include "main.h"
/**
 * built_in_exit - terminates the shell with exit
 * @args: pointer with the direction argument.
 * @line_pointer: standard input str
 * @terminate: represents exit status
 * Return: none
 */
void built_in_exit(char **args, char *line_pointer, int terminate)
{
	int stat = 0;

	if (!args[1])
	{
		free(line_pointer);
		free(args);
		exit(terminate);
	}
	stat = atoi(args[1]);

	free(line_pointer);
	free(args);
	exit(stat);
}

/**
 * get_token - function that gets string token
 * @line_pointer: user input(command)
 * Return: pointer
 */

char **get_token(char *line_pointer)
{
	size_t i = 0;
	char **user_input = NULL;
	int length = 0;
	char *token = NULL;

	if (line_pointer == NULL)
		return (NULL);

	for (i = 0; line_pointer[i]; i++)
	{
		if (line_pointer[i] == ' ')
			length++;
	}
	if ((length + 1) == string_len(line_pointer))
		return (NULL);
	user_input = malloc(sizeof(char *) * (length + 2));
	if (user_input == NULL)
		return (NULL);

	token = strtokenize(line_pointer, " \n\t\r");
	for (i = 0; token != NULL; i++)
	{
		user_input[i] = token;
		token = strtokenize(NULL, " \n\t\r");
	}
	user_input[i] = NULL;
	return (user_input);
}

/**
 *get_enviroment - comands that get all enviroment
 *@env: enviroment
 *Return: 0
 */

void get_enviroment(char **env)
{
	size_t excute = 0;

	while (env[excute])
	{
		write(STDOUT_FILENO, env[excute], string_len(env[excute]));
		write(STDOUT_FILENO, "\n", 1);
		excute++;
	}
}
