#include "main.h"
/**
 * values_path - separate the path in new strings.
 * @arg: command input of user.
 * @env: enviroment.
 * Return:  a pointer to strings.
 */
int values_path(char **arg, char **env)
{
	char *token = NULL, *relative_path = NULL, *absolute_path = NULL;
	size_t value_path, command;
	struct stat stat_lineptr;

	if (stat(*arg, &stat_lineptr) == 0)
		return (-1);
	relative_path = path_var(env);
	if (!relative_path)
		return (-1);
	token = strtokenize(relative_path, ":");
	command = string_len(*arg);
	while (token)
	{
		value_path = string_len(token);
		absolute_path = malloc(sizeof(char) * (value_path + command + 2));
		if (!absolute_path)
		{
			free(relative_path);
			return (-1);
		}
		absolute_path = string_copy(absolute_path, token);
		concat(absolute_path, "/");
		concat(absolute_path, *arg);

		if (stat(absolute_path, &stat_lineptr) == 0)
		{
			*arg = absolute_path;
			free(relative_path);
			return (0);
		}
		free(absolute_path);
		token = strtokenize(NULL, ":");
	}
	free(relative_path);
	return (-1);
}
