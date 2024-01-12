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

	switch (!args[1])
	{
	case 1:
		free(line_pointer);
		free(args);
		exit(terminate);
		break;
	default:
		break;
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

/**
 * custom_getline - custom function for get line
 * Return: 0
 */

char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index;
	static ssize_t bytes_read;
	char *line;
	size_t line_length;

	buffer_index = 0;
	bytes_read = 0;

	if (buffer_index >= (size_t)bytes_read || bytes_read == 0)
	{
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			return (NULL);
		}
		buffer_index = 0;
	}
	line = NULL;
	line_length = 0;
	while (buffer_index < (size_t)bytes_read)
	{
		if (buffer[buffer_index] == '\n')
		{
			buffer_index++;
			break;
		}
		line = realloc(line, line_length + 1);
		if (line == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		line[line_length++] = buffer[buffer_index++];
	}
	if (line != NULL)
	{
		line[line_length] = '\0';
	}
	return (line);
}
