#include "main.h"
/**
 * main - main  functions
 * @arg_c: argument numbers
 * @args: argument value
 * @env: environment
 * Return: 0.
 */
int main(int arg_c, char **args, char **env)
{
	char *getcommand = NULL, **user_input = NULL;
	int pathValue = 0, terminate = 0, n = 0;
	(void)arg_c;

	while (1)
	{
		getcommand = custom_getline();
		if (getcommand)
		{
			pathValue++;
			user_input = get_token(getcommand);
			if (!user_input)
			{
				free(getcommand);
				continue;
			}
			if ((!comp_strval(user_input[0], "exit")) && user_input[1] == NULL)
				built_in_exit(user_input, getcommand, terminate);
			if (!comp_strval(user_input[0], "env"))
				get_enviroment(env);
			else
			{
				n = values_path(&user_input[0], env);
				terminate = fork_f(user_input, args, env, getcommand, pathValue, n);
				if (n == 0)
					free(user_input[0]);
			}
			free(user_input);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(terminate);
		}
		free(getcommand);
	}
	return (terminate);
}
