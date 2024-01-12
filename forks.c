#include "main.h"
/**
 * fork_f - fork function
 *@arg: command and values path
 *@PID: integer
 *@env: environment
 *@lineptr: user input
 *@n: process id
 *@c: check
 *Return: 0
 */

int fork_f(char **arg, char **PID, char **env, char *lineptr, int n, int c)
{
	pid_t child;
	int stat;
	char *format = "%s: %d: %s: not found\n";

	child = fork();

	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, format, PID[0], n, arg[0]);
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&stat);

		if (WIFEXITED(stat) && WEXITstat(stat) != 0)
			return (WEXITstat(stat));
	}
	return (0);
}
