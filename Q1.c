#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
printf("#cisfun$ ");
}

/**
 * handle_errors - Handles errors and prints an error message
 * @message: The error message to be displayed
 */
void handle_errors(const char *message)
{
perror(message);
}


/**
 * simpleshell - test
 * Return: A pointer
 */
int simpleshell(void)
{
char *command;
size_t bufsize = 1024;
pid_t pid;
command = (char *)malloc(bufsize * sizeof(char));
	if (command == NULL)
	{
	handle_errors("malloc error");
	exit(1);
	}
while (1)
	{
	printf("$ ");
	if (getline(&command, &bufsize, stdin) == -1)
	{
	printf("\n");
	break;
	}
	if (command[strlen(command) - 1] == '\n')
	command[strlen(command) - 1] = '\0';
	pid = fork();
	if (pid == -1)
	{
	handle_errors("fork error");
	exit(1);
	}
	else if (pid == 0)
	{
		char **args = (char **)malloc(2 * sizeof(char *));
	if (args == NULL)
	{
	handle_errors("malloc error");
	exit(1);
	}
	args[0] = command;
	args[1] = NULL;
	if (execve(args[0], args, NULL) == -1)
	{
	handle_errors("execve error");
	exit(1);
	}
	free(args);
	}
	else
	{
	wait(NULL);
	}
	}
	free(command);
return (0);
}
/**
 * main - Entry point for the shell program
 * Description: The main function of the shell program. It reads
 * commands from either a file or standard input, processes the
 * commands, and executes them. If a file name is provided as a
 * command-line argument, the program reads commands from the file;
 * otherwise, it reads commands from standard input.
 *
 * Return: Always returns 0 to indicate successful execution/
 */

int main(void)
{
simpleshell();
return (0);
}
